#include "Profiler.h"
#include "FMath.h"

using namespace FRE;
void Test_Profiler();

int main()
{
	Test_Profiler();
}

void Test_Profiler()
{
	Math::Vector4f_t k;
	Math::Matrix3f_t m1;

	Profiler::Begin<CPUMarker>("Main");

	for (unsigned i = 0; i < 1000000; ++i)
	{
		Math::MatMul(m1, m1);
	}

	Profiler::Begin<CPUMarker>("SubMain");
	for (unsigned i = 0; i < 1000000; ++i)
	{
		Math::MatMul(m1, m1);
	}
	Profiler::End();

	Profiler::Begin<CPUMarker>("SubMain");
	for (unsigned i = 0; i < 1000000; ++i)
	{
		Math::MatMul(m1, m1);
	}
	Profiler::End();

	Profiler::End();

	auto mainTimes = Profiler::GetInstance().GetTicks("Main");
	auto subMainTimes = Profiler::GetInstance().GetTicks("SubMain");
}