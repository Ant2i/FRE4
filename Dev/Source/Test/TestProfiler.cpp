#include "gtest/gtest.h"
#include "Profiler.h"

using namespace FRE;

void Sleep(unsigned ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

double ToMs(t_tick t)
{
	return (t * 1000.0) / CLOCKS_PER_SEC;
}

TEST(Test_Profiler, Profiling)
{
	Profiler::Begin<CPUMarker>("Main");
		Sleep(100);
	Profiler::End();
	EXPECT_EQ(fabs(ToMs(Profiler::GetTicks(0, "Main")) - 100.0) < 1.0, true);

	Profiler::Flush();
	ASSERT_EQ(Profiler::GetTicks(0, "Main"), 0);

	Profiler::Begin<CPUMarker>("Main");
		Sleep(100);
		Profiler::Begin<CPUMarker>("SubMain");
			Sleep(100);
		Profiler::End();
		Profiler::Begin<CPUMarker>("SubMain");
			Sleep(100);
		Profiler::End();
	Profiler::End();

	auto main = ToMs(Profiler::GetTicks(0, "Main"));
	auto smain = ToMs(Profiler::GetTicks(0, "SubMain"));
	EXPECT_EQ(fabs(main - 300.0) < 3.0, true);
	EXPECT_EQ(fabs(smain - 200.0) < 3.0, true);
}