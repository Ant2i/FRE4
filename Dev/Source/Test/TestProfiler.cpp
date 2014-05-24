#include "gtest/gtest.h"
#include "Profiler.h"
#include <cmath>

using namespace FRE;

void Sleep(unsigned ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

TEST(Test_Profiler, Profiling)
{
	Profiler::Begin<CPUMarker>("Main");
		Sleep(100);
	Profiler::End();
    
	EXPECT_EQ(abs(Profiler::GetTimeIntervalMs(0, "Main") - 100) < 4, true);

	Profiler::Flush();
	ASSERT_EQ(Profiler::GetTimeIntervalMs(0, "Main"), 0);

	Profiler::Begin<CPUMarker>("Main");
		Sleep(100);
		Profiler::Begin<CPUMarker>("SubMain");
			Sleep(100);
		Profiler::End();
		Profiler::Begin<CPUMarker>("SubMain");
			Sleep(100);
		Profiler::End();
	Profiler::End();

	EXPECT_EQ(abs(Profiler::GetTimeIntervalMs(0, "Main") - 300) < 4, true);
	EXPECT_EQ(abs(Profiler::GetTimeIntervalMs(0, "SubMain") - 200) < 4, true);
}