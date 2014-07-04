#include "gtest/gtest.h"
#include "FreProfiler.h"

using namespace FRE::Utils;

void FSleep(unsigned ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

double ProfileMs(const std::string & markName)
{
	auto stat = Profiler::GetTime(0, markName);
	return stat.Max * 1E3;
}

bool Compare(double v1, double v2)
{
	double v = v1 - v2;
	return abs(v) < 3.0;
}

TEST(Test_Profiler, Profiling)
{
	CPU_PROFILE_START(Main);
		FSleep(100);
	CPU_PROFILE_STOP(Main);
    
	EXPECT_EQ(Compare(ProfileMs("Main"), 100), true);

	Profiler::Flush();
	ASSERT_EQ(ProfileMs("Main"), 0);

	CPU_PROFILE_START(Main);
		FSleep(100);
		CPU_PROFILE_START(SubMain);
			FSleep(100);
		CPU_PROFILE_STOP(SubMain);
	CPU_PROFILE_STOP(Main);

	EXPECT_EQ(Compare(ProfileMs("SubMain"), 100.0), true);
	EXPECT_EQ(Compare(ProfileMs("Main"), 200.0), true);
}