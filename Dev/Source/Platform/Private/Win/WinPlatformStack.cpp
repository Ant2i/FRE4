﻿#include "NativePlatformStack.h"

#include <Windows.h>
#include <DbgHelp.h>
#include <Shlwapi.h>
#include <TlHelp32.h>
#include <psapi.h>

#pragma comment(lib, "DbgHelp.lib")

#undef CaptureStackBackTrace

#define USE_FAST_STACKTRACE 0
#define USE_SLOW_STACKTRACE 1
#define MAX_CALLSTACK_DEPTH 128

namespace Platform
{
	void InitSysStack()
	{
		static bool initialized = false;

		if (!initialized)
		{
			BOOL res = SymInitialize(GetCurrentProcess(), nullptr, true);

			initialized = true;
		}
	}

	namespace
	{
		static int32 CaptureStackTraceHelper(uint64 *backTrace, uint32 maxDepth, CONTEXT* context)
		{
			InitSysStack();

			STACKFRAME64		stackFrame64;
			HANDLE				processHandle;
			HANDLE				threadHandle;
			unsigned long		lastError;
			bool				stackWalkSucceeded = true;
			uint32				currentDepth = 0;
			uint32				machineType = IMAGE_FILE_MACHINE_I386;
			CONTEXT				contextCopy = *context;

			__try
			{
				processHandle = GetCurrentProcess();
				threadHandle = GetCurrentThread();

				memset(&stackFrame64, sizeof(stackFrame64), 0);

				stackFrame64.AddrPC.Mode = AddrModeFlat;
				stackFrame64.AddrStack.Mode = AddrModeFlat;
				stackFrame64.AddrFrame.Mode = AddrModeFlat;

#ifdef _WIN64
				stackFrame64.AddrPC.Offset = context->Rip;
				stackFrame64.AddrStack.Offset = context->Rsp;
				stackFrame64.AddrFrame.Offset = context->Rbp;
				machineType = IMAGE_FILE_MACHINE_AMD64;
#else	
				stackFrame64.AddrPC.Offset = context->Eip;
				stackFrame64.AddrStack.Offset = context->Esp;
				stackFrame64.AddrFrame.Offset = context->Ebp;
#endif	

				while (stackWalkSucceeded && (currentDepth < maxDepth))
				{
					stackWalkSucceeded = !!StackWalk64(machineType, processHandle, threadHandle, &stackFrame64, &contextCopy, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL);

					backTrace[currentDepth++] = stackFrame64.AddrPC.Offset;

					if (!stackWalkSucceeded)
					{
						lastError = GetLastError();
						break;
					}

					if (stackFrame64.AddrFrame.Offset == 0)
					{
						break;
					}
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				return EXCEPTION_EXECUTE_HANDLER;
			}

			for (; currentDepth < maxDepth; currentDepth++)
			{
				backTrace[currentDepth] = 0;
			}

			return EXCEPTION_EXECUTE_HANDLER;
		}
	}

	void PlatformStack::CaptureStackBackTrace(uint64* backTrace, uint32 maxDepth, void* context)
	{
		if (backTrace == NULL || maxDepth == 0)
		{
			return;
		}

		if (context)
		{
			CaptureStackTraceHelper(backTrace, maxDepth, (CONTEXT*)context);
		}
		else
		{
#if USE_FAST_STACKTRACE
			//if (!GMaxCallstackDepthInitialized)
			//{
			//	DetermineMaxCallstackDepth();
			//}

			PVOID winBackTrace[MAX_CALLSTACK_DEPTH];
			uint16 numFrames = RtlCaptureStackBackTrace(0, maxDepth, winBackTrace, NULL);
			for (uint16 frameIndex = 0; frameIndex < numFrames; ++frameIndex)
			{
				backTrace[frameIndex] = (uint64)winBackTrace[frameIndex];
			}

			while (numFrames < maxDepth)
			{
				backTrace[numFrames++] = 0;
			}

#elif USE_SLOW_STACKTRACE
			InitSysStack();

			CONTEXT helperContext;
			RtlCaptureContext(&helperContext);

			CaptureStackTraceHelper(backTrace, maxDepth, &helperContext);

#elif _WIN64
			// Raise an exception so CaptureStackBackTraceHelper has access to context record.
			__try
			{
				RaiseException(0,			// Application-defined exception code.
					0,			// Zero indicates continuable exception.
					0,			// Number of arguments in args array (ignored if args is NULL)
					NULL);		// Array of arguments
			}
			// Capture the back trace.
			__except (CaptureStackTraceHelper(backTrace, maxDepth, (GetExceptionInformation())->ContextRecord))
			{
			}
#else
			// Use a bit of inline assembly to capture the information relevant to stack walking which is
			// basically EIP and EBP.
			CONTEXT HelperContext;
			memset(&HelperContext, 0, sizeof(CONTEXT));
			HelperContext.ContextFlags = CONTEXT_FULL;

			// Use a fake function call to pop the return address and retrieve EIP.
			__asm
			{
				call FakeFunctionCall
				FakeFunctionCall :
				pop eax
					mov HelperContext.Eip, eax
					mov HelperContext.Ebp, ebp
					mov HelperContext.Esp, esp
			}

			// Capture the back trace.
			CaptureStackTraceHelper(backTrace, maxDepth, &HelperContext);
#endif
		}
	}

	void PlatformStack::ProgramAddressToSymbolInfo(uint64 address, SymbolInfo& oSymbolInfo)
	{
		InitSysStack();

		oSymbolInfo.Address = address;

		uint32 lastError = 0;
		HANDLE processHandle = GetCurrentProcess();

		ansichar symbolBuffer[sizeof(IMAGEHLP_SYMBOL64) + SymbolInfo::MAX_NAME_LENGHT] = { 0 };
		IMAGEHLP_SYMBOL64* symbol = (IMAGEHLP_SYMBOL64*)symbolBuffer;
		symbol->SizeOfStruct = sizeof(symbolBuffer);
		symbol->MaxNameLength = SymbolInfo::MAX_NAME_LENGHT;

		if (SymGetSymFromAddr64(processHandle, address, nullptr, symbol))
		{
			int32 offset = 0;
			while (symbol->Name[offset] < 32 || symbol->Name[offset] > 127)
			{
				offset++;
			}

			strncpy(oSymbolInfo.FunctionName, symbol->Name + offset, SymbolInfo::MAX_NAME_LENGHT);
			strncat(oSymbolInfo.FunctionName, "()", SymbolInfo::MAX_NAME_LENGHT);
		}
		else
		{
			lastError = GetLastError();
		}

		IMAGEHLP_LINE64	imageHelpLine = { 0 };
		imageHelpLine.SizeOfStruct = sizeof(imageHelpLine);
		if (SymGetLineFromAddr64(processHandle, address, (::DWORD *)&oSymbolInfo.SymbolDisplacement, &imageHelpLine))
		{
			strncpy(oSymbolInfo.FileName, imageHelpLine.FileName, SymbolInfo::MAX_NAME_LENGHT);
			oSymbolInfo.LineNumber = imageHelpLine.LineNumber;
		}
		else
		{
			lastError = GetLastError();
		}

		IMAGEHLP_MODULE64 imageHelpModule = { 0 };
		imageHelpModule.SizeOfStruct = sizeof(imageHelpModule);
		if (SymGetModuleInfo64(processHandle, address, &imageHelpModule))
		{
			strncpy(oSymbolInfo.ModuleName, imageHelpModule.ImageName, SymbolInfo::MAX_NAME_LENGHT);
		}
		else
		{
			lastError = GetLastError();
		}
	}
}
