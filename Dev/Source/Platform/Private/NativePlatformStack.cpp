#include "NativePlatformStack.h"

namespace Platform
{
	void PlatformStack::GetStack(ISymbolInfoGet& arr, int32 ignoreCount, int32 maxDepth, void* context)
	{
		std::vector<uint64> backTrace(maxDepth);
		Platform::PlatformStack::CaptureStackBackTrace(backTrace.data(), maxDepth, context);

		for (int i = ignoreCount; i < maxDepth; ++i)
		{
			if (backTrace[i] != 0)
			{
				Platform::PlatformStack::SymbolInfo info;
				Platform::PlatformStack::ProgramAddressToSymbolInfo(backTrace[i], info);
				arr.Push(info);
			}
		}
	}
}