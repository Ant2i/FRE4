// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	LinuxPlatformStackWalk.cpp: Linux implementations of stack walk functions
=============================================================================*/

#include "CorePrivatePCH.h"
#include "Misc/App.h"
#include "LinuxPlatformCrashContext.h"
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>
#include <stdio.h>

// these are not actually system headers, but a TPS library (see ThirdParty/elftoolchain)
#include <libelf.h>
#include <_libelf.h>
#include <libdwarf.h>
#include <dwarf.h>

#ifndef DW_AT_MIPS_linkage_name
	#define DW_AT_MIPS_linkage_name		0x2007			// common extension, used before DW_AT_linkage_name became standard
#endif // DW_AT_MIPS_linkage_name

namespace Platform
{
	namespace
	{
		struct LinuxBacktraceSymbols
		{
			LinuxBacktraceSymbols() :
				inited(false),
				ExeFd(-1),
				ElfHdr(NULL),
				debugInfo(NULL)
			{
			}
			~LinuxBacktraceSymbols();

			void Init();

			bool GetInfoForAddress(void* address, const char** oModuleNamePtr, const char** oFunctionNamePtr, const char** oSourceFilePtr, int* oLineNumberPtr);

		private:
			bool inited;
			int ExeFd;
			struct _Elf* ElfHdr;
			struct _Dwarf_Debug	* debugInfo;

			static bool CheckAddressInRange(Dwarf_Debug DebugInfo, Dwarf_Die Die, Dwarf_Unsigned Addr);
			static void FindFunctionNameInDIEAndChildren(Dwarf_Debug DebugInfo, Dwarf_Die Die, Dwarf_Addr Addr, const char **OutFuncName);
			static bool FindFunctionNameInDIE(Dwarf_Debug DebugInfo, Dwarf_Die Die, Dwarf_Addr Addr, const char **OutFuncName);
			static bool FindNameAttributeInDIE(Dwarf_Die Die, const char **OutFuncName);
		};

		void LinuxBacktraceSymbols::Init()
		{
			if (!inited)
			{
				// open ourselves for examination
				bool dwarfEnable = true;
				if (dwarfEnable)
				{
					ExeFd = open("/proc/self/exe", O_RDONLY);
					if (ExeFd >= 0)
					{
						Dwarf_Error errorInfo;
						// allocate DWARF debug descriptor
						if (dwarf_init(ExeFd, DW_DLC_READ, NULL, NULL, &debugInfo, &errorInfo) == DW_DLV_OK)
						{
							// get ELF descritor
							if (dwarf_get_elf(debugInfo, &ElfHdr, &errorInfo) != DW_DLV_OK)
							{
								dwarf_finish(debugInfo, &errorInfo);
								debugInfo = NULL;

								close(ExeFd);
								ExeFd = -1;
							}
						}
						else
						{
							debugInfo = NULL;
							close(ExeFd);
							ExeFd = -1;
						}
					}
				}
				inited = true;
			}
		}

		LinuxBacktraceSymbols::~LinuxBacktraceSymbols()
		{
			if (debugInfo)
			{
				Dwarf_Error errorInfo;
				dwarf_finish(debugInfo, &errorInfo);
				debugInfo = NULL;
			}

			if (ElfHdr)
			{
				elf_end(ElfHdr);
				ElfHdr = NULL;
			}

			if (ExeFd >= 0)
			{
				close(ExeFd);
				ExeFd = -1;
			}
		}

		bool LinuxBacktraceSymbols::GetInfoForAddress(void* Address, const char** OutModuleNamePtr, const char** OutFunctionNamePtr, const char** OutSourceFilePtr, int* OutLineNumberPtr)
		{
			if (debugInfo == NULL)
			{
				return false;
			}

			Dwarf_Die Die;
			Dwarf_Unsigned Addr = reinterpret_cast<Dwarf_Unsigned>(Address), LineNumber = 0;
			const char * SrcFile = NULL;

			static_assert(sizeof(Dwarf_Unsigned) >= sizeof(Address), "Dwarf_Unsigned type should be long enough to represent pointers. Check libdwarf bitness.");

			int ReturnCode = DW_DLV_OK;
			Dwarf_Error ErrorInfo;
			bool bExitHeaderLoop = false;
			int32 MaxCompileUnitsAllowed = 16 * 1024 * 1024;	// safeguard to make sure we never get into an infinite loop
			const int32 kMaxBufferLinesAllowed = 16 * 1024 * 1024;	// safeguard to prevent too long line loop
			for (;;)
			{
				if (--MaxCompileUnitsAllowed <= 0)
				{
					fprintf(stderr, "Breaking out from what seems to be an infinite loop during DWARF parsing (too many compile units).\n");
					ReturnCode = DW_DLE_DIE_NO_CU_CONTEXT;	// invalidate
					break;
				}

				if (bExitHeaderLoop)
					break;

				ReturnCode = dwarf_next_cu_header(debugInfo, NULL, NULL, NULL, NULL, NULL, &ErrorInfo);
				if (ReturnCode != DW_DLV_OK)
					break;

				Die = NULL;

				while (dwarf_siblingof(debugInfo, Die, &Die, &ErrorInfo) == DW_DLV_OK)
				{
					Dwarf_Half Tag;
					if (dwarf_tag(Die, &Tag, &ErrorInfo) != DW_DLV_OK)
					{
						bExitHeaderLoop = true;
						break;
					}

					if (Tag == DW_TAG_compile_unit)
					{
						break;
					}
				}

				if (Die == NULL)
				{
					break;
				}

				// check if address is inside this CU
				if (!CheckAddressInRange(debugInfo, Die, Addr))
				{
					continue;
				}

				Dwarf_Line * LineBuf;
				Dwarf_Signed NumLines = kMaxBufferLinesAllowed;
				if (dwarf_srclines(Die, &LineBuf, &NumLines, &ErrorInfo) != DW_DLV_OK)
				{
					// could not get line info for some reason
					continue;
				}

				if (NumLines >= kMaxBufferLinesAllowed)
				{
					fprintf(stderr, "Number of lines associated with a DIE looks unreasonable (%d), early quitting.\n", static_cast<int32>(NumLines));
					ReturnCode = DW_DLE_DIE_NO_CU_CONTEXT;	// invalidate
					break;
				}

				// look which line is that
				Dwarf_Addr LineAddress, PrevLineAddress = ~0ULL;
				Dwarf_Unsigned LineIdx = NumLines;
				for (int Idx = 0; Idx < NumLines; ++Idx)
				{
					if (dwarf_lineaddr(LineBuf[Idx], &LineAddress, &ErrorInfo) != 0)
					{
						bExitHeaderLoop = true;
						break;
					}
					// check if we hit the exact line
					if (Addr == LineAddress)
					{
						LineIdx = Idx;
						bExitHeaderLoop = true;
						break;
					}
					else if (PrevLineAddress < Addr && Addr < LineAddress)
					{
						LineIdx = Idx - 1;
						break;
					}
					PrevLineAddress = LineAddress;
				}
				if (LineIdx < NumLines)
				{
					if (dwarf_lineno(LineBuf[LineIdx], &LineNumber, &ErrorInfo) != 0)
					{
						fprintf(stderr, "Can't get line number by dwarf_lineno.\n");
						break;
					}
					for (int Idx = LineIdx; Idx >= 0; --Idx)
					{
						char * SrcFileTemp = NULL;
						if (!dwarf_linesrc(LineBuf[Idx], &SrcFileTemp, &ErrorInfo))
						{
							SrcFile = SrcFileTemp;
							break;
						}
					}
					bExitHeaderLoop = true;
				}
			}

			bool bSuccess = (ReturnCode == DW_DLV_OK);

			if (LIKELY(bSuccess))
			{
				if (LIKELY(OutFunctionNamePtr != nullptr))
				{
					const char * FunctionName = nullptr;
					FindFunctionNameInDIEAndChildren(debugInfo, Die, Addr, &FunctionName);
					if (LIKELY(FunctionName != nullptr))
					{
						*OutFunctionNamePtr = FunctionName;
					}
					else
					{
						// make sure it's not null
						*OutFunctionNamePtr = "Unknown";
					}
				}

				if (LIKELY(OutSourceFilePtr != nullptr && OutLineNumberPtr != nullptr))
				{
					if (SrcFile != nullptr)
					{
						*OutSourceFilePtr = SrcFile;
						*OutLineNumberPtr = LineNumber;
					}
					else
					{
						*OutSourceFilePtr = "Unknown";
						*OutLineNumberPtr = -1;
					}
				}

				if (LIKELY(OutModuleNamePtr != nullptr))
				{
					const char* ModuleName = nullptr;

					Dl_info DlInfo;
					if (dladdr(Address, &DlInfo) != 0)
					{
						if (DlInfo.dli_fname != nullptr)
						{
							ModuleName = DlInfo.dli_fname;	// this is a pointer we don't own, but assuming it's good until at least the next dladdr call
						}
					}

					if (LIKELY(ModuleName != nullptr))
					{
						*OutModuleNamePtr = ModuleName;
					}
					else
					{
						*OutModuleNamePtr = "Unknown";
					}
				}
			}

			// Resets internal CU pointer, so next time we get here it begins from the start
			while (ReturnCode != DW_DLV_NO_ENTRY)
			{
				if (ReturnCode == DW_DLV_ERROR)
				{
					break;
				}
				ReturnCode = dwarf_next_cu_header(debugInfo, NULL, NULL, NULL, NULL, NULL, &ErrorInfo);
			}

			return bSuccess;
		}

		bool LinuxBacktraceSymbols::CheckAddressInRange(Dwarf_Debug DebugInfo, Dwarf_Die Die, Dwarf_Unsigned Addr)
		{
			Dwarf_Attribute *AttrList;
			Dwarf_Signed AttrCount;

			if (UNLIKELY(dwarf_attrlist(Die, &AttrList, &AttrCount, NULL) != DW_DLV_OK))
			{
				// assume not in range if we couldn't get the information
				return false;
			}

			Dwarf_Addr LowAddr = 0, HighAddr = 0, HighOffset = 0;

			for (int i = 0; i < AttrCount; i++)
			{
				Dwarf_Half Attr;
				if (dwarf_whatattr(AttrList[i], &Attr, nullptr) != DW_DLV_OK)
				{
					continue;
				}

				switch (Attr)
				{
				case DW_AT_low_pc:
				{
					Dwarf_Addr TempLowAddr;
					if (dwarf_formaddr(AttrList[i], &TempLowAddr, nullptr) == DW_DLV_OK)
					{
						if (LIKELY(TempLowAddr > Addr))	// shortcut
						{
							return false;
						}

						LowAddr = TempLowAddr;
					}
				}
				break;

				case DW_AT_high_pc:
				{
					Dwarf_Addr TempHighAddr;
					if (dwarf_formaddr(AttrList[i], &TempHighAddr, nullptr) == DW_DLV_OK)
					{
						if (LIKELY(TempHighAddr <= Addr))	// shortcut
						{
							return false;
						}

						HighAddr = TempHighAddr;
					}

					// Offset is used since DWARF-4. Store it, but don't compare right now in case
					// we haven't yet initialized LowAddr
					Dwarf_Unsigned TempHighOffset;
					if (dwarf_formudata(AttrList[i], &TempHighOffset, nullptr) == DW_DLV_OK)
					{
						HighOffset = TempHighOffset;
					}
				}
				break;

				case DW_AT_ranges:
				{
					Dwarf_Unsigned Offset;
					if (dwarf_formudata(AttrList[i], &Offset, NULL) != DW_DLV_OK)
					{
						continue;
					}

					Dwarf_Ranges *Ranges;
					Dwarf_Signed Count;
					if (dwarf_get_ranges(DebugInfo, (Dwarf_Off)Offset, &Ranges, &Count, nullptr, nullptr) != DW_DLV_OK)
					{
						continue;
					}

					for (int j = 0; j < Count; j++)
					{
						if (Ranges[j].dwr_type == DW_RANGES_END)
						{
							break;
						}
						if (Ranges[j].dwr_type == DW_RANGES_ENTRY)
						{
							if ((Ranges[j].dwr_addr1 <= Addr) && (Addr < Ranges[j].dwr_addr2))
							{
								return true;
							}
							continue;
						}
					}
					return false;
				}
				break;

				default:
					break;
				}
			}

			if (UNLIKELY(HighAddr == 0 && HighOffset != 0))
			{
				HighAddr = LowAddr + HighOffset;
			}

			return LowAddr <= Addr && Addr < HighAddr;
		}

		bool LinuxBacktraceSymbols::FindNameAttributeInDIE(Dwarf_Die Die, const char **OutFuncName)
		{
			Dwarf_Error ErrorInfo;
			int ReturnCode;

			// look first for DW_AT_linkage_name or DW_AT_MIPS_linkage_name, since they hold fully qualified (albeit mangled) name
			Dwarf_Attribute LinkageNameAt;
			// DW_AT_MIPS_linkage_name is preferred because we're using DWARF2 by default
			ReturnCode = dwarf_attr(Die, DW_AT_MIPS_linkage_name, &LinkageNameAt, &ErrorInfo);
			if (UNLIKELY(ReturnCode == DW_DLV_NO_ENTRY))
			{
				// retry with newer DW_AT_linkage_name
				ReturnCode = dwarf_attr(Die, DW_AT_linkage_name, &LinkageNameAt, &ErrorInfo);
			}

			if (LIKELY(ReturnCode == DW_DLV_OK))
			{
				char *TempFuncName;
				if (LIKELY(dwarf_formstring(LinkageNameAt, &TempFuncName, &ErrorInfo) == DW_DLV_OK))
				{
					// try to demangle
					int DemangleStatus = 0xBAD;
					char *Demangled = abi::__cxa_demangle(TempFuncName, nullptr, nullptr, &DemangleStatus);
					if (DemangleStatus == 0 && Demangled != nullptr)
					{
						// cache the demangled name
						static char CachedDemangledName[1024];
						FCStringAnsi::Strcpy(CachedDemangledName, sizeof(CachedDemangledName), Demangled);

						*OutFuncName = CachedDemangledName;
					}
					else
					{
						*OutFuncName = TempFuncName;
					}

					if (Demangled)
					{
						free(Demangled);
					}
					return true;
				}
			}

			// if everything else fails, just take DW_AT_name, but in case of class methods, it is only a method name, so the information will be incomplete and almost useless
			const char *TempMethodName;
			if (LIKELY(dwarf_attrval_string(Die, DW_AT_name, &TempMethodName, &ErrorInfo) == DW_DLV_OK))
			{
				*OutFuncName = TempMethodName;
				return true;
			}

			return false;
		}

		bool LinuxBacktraceSymbols::FindFunctionNameInDIE(Dwarf_Debug DebugInfo, Dwarf_Die Die, Dwarf_Addr Addr, const char **OutFuncName)
		{
			Dwarf_Error ErrorInfo;
			Dwarf_Half Tag;

			if (dwarf_tag(Die, &Tag, &ErrorInfo) != DW_DLV_OK || Tag != DW_TAG_subprogram)
			{
				return false;
			}

			// check if address is inside this entry
			if (!CheckAddressInRange(DebugInfo, Die, Addr))
			{
				return false;
			}

			// attempt to find the name in DW_TAG_subprogram DIE
			if (FindNameAttributeInDIE(Die, OutFuncName))
			{
				return true;
			}

			// If not found, navigate to specification DIE and look there
			Dwarf_Attribute SpecAt;
			if (UNLIKELY(dwarf_attr(Die, DW_AT_specification, &SpecAt, &ErrorInfo) != DW_DLV_OK))
			{
				// no specificaation die
				return false;
			}

			Dwarf_Off Offset;
			if (UNLIKELY(dwarf_global_formref(SpecAt, &Offset, &ErrorInfo) != DW_DLV_OK))
			{
				return false;
			}

			Dwarf_Die SpecDie;
			if (UNLIKELY(dwarf_offdie(DebugInfo, Offset, &SpecDie, &ErrorInfo) != DW_DLV_OK))
			{
				return false;
			}

			return FindNameAttributeInDIE(SpecDie, OutFuncName);
		}

		void LinuxBacktraceSymbols::FindFunctionNameInDIEAndChildren(Dwarf_Debug DebugInfo, Dwarf_Die Die, Dwarf_Addr Addr, const char **OutFuncName)
		{
			if (OutFuncName == NULL || *OutFuncName != NULL)
			{
				return;
			}

			// search for this Die
			if (FindFunctionNameInDIE(DebugInfo, Die, Addr, OutFuncName))
			{
				return;
			}

			Dwarf_Die PrevChild = Die, Current = NULL;
			Dwarf_Error ErrorInfo;

			int32 MaxChildrenAllowed = 32 * 1024 * 1024;	// safeguard to make sure we never get into an infinite loop
			for (;;)
			{
				if (--MaxChildrenAllowed <= 0)
				{
					fprintf(stderr, "Breaking out from what seems to be an infinite loop during DWARF parsing (too many children).\n");
					return;
				}

				// Get the child
				if (dwarf_child(PrevChild, &Current, &ErrorInfo) != DW_DLV_OK)
				{
					return;	// bail out
				}

				PrevChild = Current;

				// look for in the child
				if (FindFunctionNameInDIE(DebugInfo, Current, Addr, OutFuncName))
				{
					return;	// got the function name!
				}

				// search among child's siblings
				int32 MaxSiblingsAllowed = 64 * 1024 * 1024;	// safeguard to make sure we never get into an infinite loop
				for (;;)
				{
					if (--MaxSiblingsAllowed <= 0)
					{
						fprintf(stderr, "Breaking out from what seems to be an infinite loop during DWARF parsing (too many siblings).\n");
						break;
					}

					Dwarf_Die Prev = Current;
					if (dwarf_siblingof(DebugInfo, Prev, &Current, &ErrorInfo) != DW_DLV_OK || Current == NULL)
					{
						break;
					}

					if (FindFunctionNameInDIE(DebugInfo, Current, Addr, OutFuncName))
					{
						return;	// got the function name!
					}
				}
			};
		}

		inline LinuxBacktraceSymbols *GetBacktraceSymbols()
		{
			static LinuxBacktraceSymbols symbols;
			symbols.Init();
			return &symbols;
		}
	}

	void FLinuxPlatformStackWalk::ProgramCounterToSymbolInfo(uint64 address, SymbolInfo& oSymbolInfo)
	{
		// Set the program counter.
		out_SymbolInfo.Address = address;

		// Get function, filename and line number.
		const char* moduleName = nullptr;
		const char* functionName = nullptr;
		const char* sourceFilename = nullptr;
		int lineNumber = 0;

		if (GetBacktraceSymbols()->GetInfoForAddress(reinterpret_cast<void*>(address), &moduleName, &functionName, &sourceFilename, &lineNumber))
		{
			oSymbolInfo.LineNumber = lineNumber;

			if (LIKELY(ModuleName != nullptr))
			{
				strcpy(oSymbolInfo.ModuleName, sizeof(oSymbolInfo.ModuleName), moduleName);
			}

			if (LIKELY(SourceFilename != nullptr))
			{
				strcpy(oSymbolInfo.FileName, sizeof(oSymbolInfo.FileName), sourceFilename);
			}

			if (FunctionName != nullptr)
			{
				strcpy(oSymbolInfo.FunctionName, sizeof(oSymbolInfo.FileName), functionName);
			}
			else
			{
				sprintf(oSymbolInfo.FunctionName, "0x%016llx", address);
			}
		}
	}

	void FLinuxPlatformStackWalk::CaptureStackBackTrace(uint64* backTrace, uint32 maxDepth, void* context)
	{
		if (backTrace == NULL || maxDepth == 0)
		{
			return;
		}

		const size_t size = backtrace(reinterpret_cast<void**>(backTrace), maxDepth);

		//if (Context)
		//{
		//	FLinuxCrashContext* LinuxContext = reinterpret_cast< FLinuxCrashContext* >( Context );

		//	if (LinuxContext->BacktraceSymbols == NULL)
		//	{
		//		LinuxContext->BacktraceSymbols = backtrace_symbols(reinterpret_cast< void** >( BackTrace ), MaxDepth);
		//	}
		//}
	}

}