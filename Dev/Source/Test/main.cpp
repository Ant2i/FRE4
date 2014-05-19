#include "Profiler.h"
#include "FMath.h"
#include "FMemory.h"
#include "FBitSet.h"

#include <sstream>

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

	auto mainTimes = Profiler::GetInstance().GetTicks(0, "Main");
	auto subMainTimes = Profiler::GetInstance().GetTicks(0, "SubMain");
    
    printf("Profile SubMain: %i \n", subMainTimes);
    printf("Profile Main: %i \n", mainTimes);
    
    ChunkMemory<int *> chunkMemory;
    auto allocres = chunkMemory.Allocate((int *)10);
	allocres = chunkMemory.Allocate((int *)20);
	

	BitSet<100> bitset;
	bitset.Reset();
	
	for (unsigned i = 0; i < 100; ++i)
		bitset.Set(i);
		
	bitset.Set(99, 0);

	auto res = bitset.FindZiroBit();

	//std::string text;
	//std::stringstream ss;
	//for (int i = 0; i < 256; ++i)
	//{
	//	char num = 1;
	//	unsigned j = 0;
	//	for (; j < 8; ++j)
	//	{
	//		if (~i & num)
	//			break;
	//		num <<= 1;
	//	}

	//	ss << "\\" << j << ":" << i << "\n";
	//}

	//text = ss.str();

	//unsigned char d = 256;
}