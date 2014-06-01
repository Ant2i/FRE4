#include "gtest/gtest.h"
#include "FMemory.h"

using namespace FRE;

class Test_FixedMemory : public ::testing::Test
{
public:
	enum 
	{
		Size = 100000
	};

protected:
	Utils::FixedMemory<int, Size> _memory;
};

TEST_F(Test_FixedMemory, Allocate)
{
	for (int i = 0; i < Test_FixedMemory::Size; ++i)
		_memory.Allocate(i);
	ASSERT_EQ(_memory.Count(), Test_FixedMemory::Size);
}

TEST_F(Test_FixedMemory, Set)
{
	for (int i = 0; i < Test_FixedMemory::Size; ++i)
		_memory.Allocate(i, i);
	ASSERT_EQ(_memory.Count(), Test_FixedMemory::Size);
}

TEST_F(Test_FixedMemory, Free)
{
	for (int i = 0; i < Test_FixedMemory::Size; ++i)
		_memory.Allocate(i, i);

	for (int i = 0; i < Test_FixedMemory::Size; ++i)
		_memory.Free(i);

	ASSERT_EQ(_memory.Count(), 0);
}

//-----------------------------------------------------------------------------

class Test_ChunkMemory : public ::testing::Test
{
public:
	enum 
	{
		Size = 1000000
	};

protected:
	Utils::ChunkMemory<int, 10000> _memory;
};

TEST_F(Test_ChunkMemory, Allocate)
{
	for (int i = 0; i < Test_ChunkMemory::Size; ++i)
		_memory.Allocate(i);
	ASSERT_EQ(_memory.Count(), Test_ChunkMemory::Size);
}

TEST_F(Test_ChunkMemory, Set)
{
	for (int i = 0; i < Test_ChunkMemory::Size; ++i)
		_memory.Allocate(i, i);
	ASSERT_EQ(_memory.Count(), Test_ChunkMemory::Size);
}

TEST(Test_New, NewTest)
{
    for (int i = 0; i < Test_ChunkMemory::Size; ++i)
		new int(i);
	ASSERT_EQ(1, 1);

}