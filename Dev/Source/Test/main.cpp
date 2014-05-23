//#include "Profiler.h"
//#include "FMath.h"
//#include "FMemory.h"

#include "gtest/gtest.h"

//using namespace FRE;
//void Test_Profiler();

//int main()
//{
//	Test_Profiler();
//}
//
//void Test_Profiler()
//{
//	Math::Vector4f_t k;
//	Math::Matrix3f_t m1(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
//	Math::Matrix3f_t m2(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
//
//	Profiler::Begin<CPUMarker>("Main");
//
//	for (unsigned i = 0; i < 100000; ++i)
//	{
//		Math::MatMul(m1, m2);
//	}
//
//	Profiler::Begin<CPUMarker>("SubMain");
//	for (unsigned i = 0; i < 100000; ++i)
//	{
//		Math::MatMul(m1, m2);
//	}
//	Profiler::End();
//
//	Profiler::Begin<CPUMarker>("SubMain");
//	for (unsigned i = 0; i < 100000; ++i)
//	{
//		Math::MatMul(m1, m2);
//	}
//	Profiler::End();
//
//	Profiler::End();
// 
//    Utils::ChunkData<int, unsigned> chunkData;
//    auto allocres = chunkData.Allocate(10);
//	allocres = chunkData.Allocate(20);
//	
//	auto * bitset = new Utils::BitSet<unsigned, 10000>();
//	//auto * bitset2 = new BitSet<unsigned, 10000>(*bitset);
//
//    Profiler::Begin<CPUMarker>("BitSet_Reset");
//	bitset->Reset();
//    Profiler::End();
//	
//    Profiler::Begin<CPUMarker>("BitSet_Set");
//	for (unsigned i = 0; i < 100; ++i)
//		bitset->Set(i);
//    Profiler::End();
//		
//	//bitset->Set(999999, 0);
//    //bitset->Set(647584, 0);
//
//    Profiler::Begin<CPUMarker>("BitSet_FindZeroBit");
//	auto res = bitset->FindZeroBit();
//    Profiler::End();
//    
//    Profiler::Begin<CPUMarker>("BitSet_Count");
//	auto count = bitset->Count();
//    Profiler::End();
//    
//	Math::Matrix3f_t m3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
//	float p = m3[0][0];
//	printf("Profile SubMain: %u %4.2f \n", Profiler::GetInstance().GetTicks(0, "SubMain"), 1.0f);
//	printf("Profile Main: %i \n", Profiler::GetInstance().GetTicks(0, "Main"));
//    printf("BitSet_Reset: %u \n", Profiler::GetInstance().GetTicks(0, "BitSet_Reset"));
//    printf("BitSet_Set: %u \n", Profiler::GetInstance().GetTicks(0, "BitSet_Set"));
//	double findTime = Profiler::GetInstance().GetTicks(0, "BitSet_FindZeroBit") / (double)CLOCKS_PER_SEC;
//    printf("BitSet_FindZeroBit: %f %u\n", findTime, res.second);
//    printf("BitSet_Count: %u %u\n", Profiler::GetInstance().GetTicks(0, "BitSet_Count"), count);
//
//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}