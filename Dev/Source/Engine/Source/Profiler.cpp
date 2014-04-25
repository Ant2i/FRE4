#include "Profiler.h"

namespace FRE
{
	Profiler & Profiler::GetInstance()
	{
		static Profiler sProfiler;
		return sProfiler;
	}

	void Profiler::BeginFrame()
	{

	}

	void Profiler::EndFrame()
	{

	}

	unsigned CPUProfile::GetCount() const
	{
		return 0;
	}

	int CPUProfile::GetTime(int num) const
	{

	}
	
	void Test_Profiler()
	{
		auto profiler = CPUProfile::Begin("Name");
	}
}

