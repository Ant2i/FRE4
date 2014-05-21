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
 
    printf("Profile SubMain: %i %f\n", Profiler::GetInstance().GetTicks(0, "SubMain"), m1[0][0]);
    printf("Profile Main: %i \n", Profiler::GetInstance().GetTicks(0, "Main"));
    
    ChunkMemory<int *> chunkMemory;
    auto allocres = chunkMemory.Allocate((int *)10);
	allocres = chunkMemory.Allocate((int *)20);

	auto * bitset = new BitSet<100000000>();
    Profiler::Begin<CPUMarker>("BitSet_Reset");
	bitset->Reset();
    Profiler::End();
	
    Profiler::Begin<CPUMarker>("BitSet_Set");
	for (unsigned i = 0; i < 100000000; ++i)
		bitset->Set(i);
    Profiler::End();
		
	bitset->Set(999999, 0);
    bitset->Set(647584, 0);

    Profiler::Begin<CPUMarker>("BitSet_FindZeroBit");
	auto res = bitset->FindZeroBit();
    Profiler::End();
    
    Profiler::Begin<CPUMarker>("BitSet_Count");
	auto count = bitset->Count();
    Profiler::End();
    
    printf("BitSet_Reset: %u \n", Profiler::GetInstance().GetTicks(0, "BitSet_Reset"));
    printf("BitSet_Set: %u \n", Profiler::GetInstance().GetTicks(0, "BitSet_Set"));
    printf("BitSet_FindZeroBit: %f %u\n", Profiler::GetInstance().GetTicks(0, "BitSet_FindZeroBit")/CLOCKS_PER_SEC, res.second);
    printf("BitSet_Count: %u %u\n", Profiler::GetInstance().GetTicks(0, "BitSet_Count"), count);
}