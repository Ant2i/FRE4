#include "gtest/gtest.h"
#include "FBitSet.h"

using namespace FRE;

class Test_BitSet : public ::testing::Test
{
public:
	enum 
	{
		BitsCount = 1000000
	};

protected:
	void SetUp()
	{
		
	}

	void TearDown()
	{
		
	}

	Utils::BitSet<BitsCount> _bitset;
};

TEST_F(Test_BitSet, Reset)
{
	_bitset.Reset();

	ASSERT_EQ(_bitset.Get(0), false);
	ASSERT_EQ(_bitset.Get(BitsCount - 1), false);
}

TEST_F(Test_BitSet, Count)
{
	ASSERT_EQ(_bitset.Count(), 0);
	_bitset.Set(200);
	ASSERT_EQ(_bitset.Count(), 1);
	_bitset.Set(BitsCount - 1);
	ASSERT_EQ(_bitset.Count(), 2);
}

TEST_F(Test_BitSet, FindZeroBit)
{
	for (unsigned i = 0; i < BitsCount; ++i)
		_bitset.Set(i);

	_bitset.Set(BitsCount - 1, 0);
	auto res = _bitset.FindZeroBit();

	ASSERT_EQ(res.first, true);
	ASSERT_EQ(res.second, BitsCount - 1);
}

TEST_F(Test_BitSet, Copy)
{
	_bitset.Set(765);
	_bitset.Set(64450);

	auto copyBits(_bitset);
		
	ASSERT_EQ(copyBits.Count(), 2);
	ASSERT_EQ(copyBits.Count(), _bitset.Count());
	ASSERT_EQ(copyBits.Get(765), true);
	ASSERT_EQ(copyBits.Get(64450), true);
}