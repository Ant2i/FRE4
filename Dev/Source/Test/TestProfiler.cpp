#include "gtest/gtest.h"
#include "FreProfiler.h"

using namespace FRE::Utils;

void FSleep(unsigned ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int long long ProfileMs(const std::string & markName)
{
	auto stat = FProfiler::GetTime(0, markName);
	return stat.Max * 1E3;
}

TEST(Test_Profiler, Profiling)
{
	CPU_PROFILE_START(Main);
		FSleep(100);
	CPU_PROFILE_STOP(Main);
    
	auto tmain = ProfileMs("Main") - 100;
	EXPECT_EQ(tmain < 4 && tmain > -4, true);

	FProfiler::Flush();
	ASSERT_EQ(ProfileMs("Main"), 0);

	CPU_PROFILE_START(Main);
		FSleep(100);
		CPU_PROFILE_START(SubMain);
			FSleep(100);
		CPU_PROFILE_STOP(SubMain);
	CPU_PROFILE_STOP(Main);

	tmain = ProfileMs("Main") - 200;
	auto tsubmain = ProfileMs("SubMain") - 100;
	EXPECT_EQ(tmain < 4 && -4 < tmain, true);
	EXPECT_EQ(tsubmain < 4 && tsubmain > -4, true);
}