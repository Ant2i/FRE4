#pragma once

#include "Platform.h"

#include <vector>

namespace Platform
{
	class PlatformStack
	{
	public:
		struct SymbolInfo
		{
			enum
			{
				MAX_NAME_LENGHT = 1024,
			};

			ansichar ModuleName[MAX_NAME_LENGHT];
			ansichar FunctionName[MAX_NAME_LENGHT];
			ansichar FileName[MAX_NAME_LENGHT];

			int32 LineNumber;
			int32 SymbolDisplacement;
			int64 OffsetInModule;
			int64 Address;
		};

		class ISymbolInfoGet
		{
		public:
			virtual void Push(const SymbolInfo& info) = 0;
		};

		static void GetStack(ISymbolInfoGet&, int32 ignoreCount, int32 maxDepth = 100, void* context = nullptr);

		static void CaptureStackBackTrace(uint64* backTrace, uint32 maxDepth, void* context = nullptr);
		static void ProgramAddressToSymbolInfo(uint64 address, SymbolInfo& oInfo);
	};

	//-------------------------------------------------------------------------

	class ArraySymbolInfoGet : public PlatformStack::ISymbolInfoGet
	{
	public:
		typedef std::vector<PlatformStack::SymbolInfo> SymbolInfoArray;

		ArraySymbolInfoGet(SymbolInfoArray& stack) :
			_stack(stack)
		{

		}

		virtual void Push(const PlatformStack::SymbolInfo& info) override
		{
			_stack.push_back(info);
		}

		SymbolInfoArray& _stack;
	};
}
