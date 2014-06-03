#include "gtest/gtest.h"
#include "FMemory.h"

#include <map>
#include <unordered_map>
#include <random>
//#include <sparse_hash_map>

using namespace FRE;

//class Test_FixedMemory : public ::testing::Test
//{
//public:
//	enum 
//	{
//		Size = 100000
//	};
//
//protected:
//	Utils::FixedMemory<int, Size> _memory;
//};
//
//TEST_F(Test_FixedMemory, Allocate)
//{
//	for (int i = 0; i < Test_FixedMemory::Size; ++i)
//		_memory.Allocate(i);
//	ASSERT_EQ(_memory.Count(), Test_FixedMemory::Size);
//}
//
//TEST_F(Test_FixedMemory, Set)
//{
//	for (int i = 0; i < Test_FixedMemory::Size; ++i)
//		_memory.Allocate(i, i);
//	ASSERT_EQ(_memory.Count(), Test_FixedMemory::Size);
//}
//
//TEST_F(Test_FixedMemory, Free)
//{
//	for (int i = 0; i < Test_FixedMemory::Size; ++i)
//		_memory.Allocate(i, i);
//
//	for (int i = 0; i < Test_FixedMemory::Size; ++i)
//		_memory.Free(i);
//
//	ASSERT_EQ(_memory.Count(), 0);
//}
//
////-----------------------------------------------------------------------------
//
//class Test_ChunkMemory : public ::testing::Test
//{
//public:
//	enum 
//	{
//		Size = 1000000
//	};
//
//protected:
//	Utils::ChunkMemory<int, 10000> _memory;
//};
//
//TEST_F(Test_ChunkMemory, Allocate)
//{
//	for (int i = 0; i < Test_ChunkMemory::Size; ++i)
//		_memory.Allocate(i);
//	ASSERT_EQ(_memory.Count(), Test_ChunkMemory::Size);
//}
//
//TEST_F(Test_ChunkMemory, Set)
//{
//	for (int i = 0; i < Test_ChunkMemory::Size; ++i)
//		_memory.Allocate(i, i);
//	ASSERT_EQ(_memory.Count(), Test_ChunkMemory::Size);
//}

//class Test_Map : public ::testing::Test
//{
//public:
//	enum 
//	{
//		Size = 100000
//	};
//
//	virtual void SetUp() override
//	{
//		for (unsigned i = 0; i < Test_Map::Size; ++i)
//		{
//			_map.insert(std::make_pair(i, i));
//			_u_map.insert(std::make_pair(i, i));
//		}
//	}
//
//protected:
//	static std::map<unsigned, unsigned> _map;
//	static std::unordered_map<unsigned, unsigned> _u_map;
//	//static sparse_hash_map
//};
//
//std::map<unsigned, unsigned> Test_Map::_map;
//std::unordered_map<unsigned, unsigned> Test_Map::_u_map(1000000);
//
//TEST_F(Test_Map, FindMap)
//{
//	std::mt19937 eng;
//	std::uniform_int_distribution<unsigned> random(0, Test_Map::Size);
//	
//	for (unsigned i = 0; i < Test_Map::Size; ++i)
//	{
//		const unsigned r = random(eng);
//		auto it = _map.find(r);
//		if (it != _map.end())
//		{
//			ASSERT_EQ(r, it->second);
//		}
//	}
//}
//
//TEST_F(Test_Map, FindHash)
//{
//	std::mt19937 eng;
//	std::uniform_int_distribution<unsigned> random(0, Test_Map::Size);
//
//	for (unsigned i = 0; i < Test_Map::Size; ++i)
//	{
//		const unsigned r = random(eng);
//		auto it = _u_map.find(r);
//		if (it != _u_map.end())
//		{
//			ASSERT_EQ(r, it->second);
//		}
//	}
//}

TEST(Test_PoolChunk, Allocate)
{
	const unsigned PoolSize = 1000000;
	Utils::FPoolChunk<unsigned> poolChunk(sizeof(float), PoolSize);

	float ** p = new float*[PoolSize];
	for (int i = 0; i < PoolSize; ++i)
	{
		p[i] = (float *)poolChunk.Allocate();
		*p[i] = (float)i;
	}
	ASSERT_EQ(poolChunk.IsFull(), true);
	ASSERT_EQ(poolChunk.Allocate(), nullptr);

	for (int i = 0; i < PoolSize; ++i)
		 poolChunk.Deallocate(p[i]);
	ASSERT_EQ(poolChunk.IsEmpty(), true);

	for (int i = 0; i < PoolSize; ++i)
	{
		p[i] = (float *)poolChunk.Allocate();
		*p[i] = (float)i;
	}

	poolChunk.Deallocate(p[PoolSize/2]);
	ASSERT_EQ(poolChunk.IsFull(), false);
	ASSERT_EQ(poolChunk.IsEmpty(), false);

	void * newP = poolChunk.Allocate();
	ASSERT_EQ(p[PoolSize/2], newP);
}

struct Foo
{
	Foo(unsigned p1, unsigned p2)
	{
		_p1 = p1;
		_p2 = p2;
	}

	unsigned _p1;
	unsigned _p2;
};

TEST(Test_PoolMemory, Allocate)
{
	const unsigned PoolSize = 1000000;
	Utils::FPoolMemory<Foo, PoolSize / 10> poolAllocator;

	for (unsigned i = 0; i < PoolSize; ++i)
	{
		auto pointer = poolAllocator.Allocate();
		if (pointer)
			new (pointer) Foo(i, i);
	}

	ASSERT_EQ(true, true);
}

TEST(Test_Heap, Allocate)
{
	const unsigned PoolSize = 1000000;
	for (unsigned i = 0; i < PoolSize; ++i)
	{
		new Foo(i, i);
	}

	ASSERT_EQ(true, true);
}