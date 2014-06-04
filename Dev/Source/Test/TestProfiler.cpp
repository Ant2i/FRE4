#include "gtest/gtest.h"
#include "FProfiler.h"
//#include <cmath>

using namespace FRE::Utils;

void FSleep(unsigned ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int long long ProfileMs(const std::string & markName)
{
	return FProfiler::GetMarkerTime(0, markName) * 1E3;
}

TEST(Test_Profiler, Profiling)
{
	FProfiler::Start<FCPUMarker>("Main");
		FSleep(100);
	FProfiler::Stop();
    
	auto tmain = ProfileMs("Main") - 100;
	EXPECT_EQ(tmain < 4 && tmain > -4, true);

	FProfiler::Flush();
	ASSERT_EQ(ProfileMs("Main"), 0);

	FProfiler::Start<FCPUMarker>("Main");
		FSleep(100);
		FProfiler::Start<FCPUMarker>("SubMain");
			FSleep(100);
		FProfiler::Stop();
		FProfiler::Start<FCPUMarker>("SubMain");
			FSleep(100);
		FProfiler::Stop();
	FProfiler::Stop();

	tmain = ProfileMs("Main") - 300;
	auto tsubmain = ProfileMs("SubMain") - 200;
	EXPECT_EQ(tmain < 4 && -4 < tmain, true);
	EXPECT_EQ(tsubmain < 4 && tsubmain > -4, true);
}