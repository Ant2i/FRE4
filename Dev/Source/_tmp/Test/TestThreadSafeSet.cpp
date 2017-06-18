#include "gtest/gtest.h"
#include "FSafeCont.h"

struct Item
{
	Item(int v) : Value(v)
	{}

	int Value = 0;
};

struct ItemLess
{
	typedef Item Type;
	typedef int CompareType;

	bool operator()(const Type left, const Type right) const
	{
		return left.Value < right.Value;
	}

	bool operator()(const Type left, CompareType value) const
	{
		return left.Value < value;
	}
};

TEST(Test_ThreadSafeSet, Add)
{
	Item item1(10);
	Item item2(2);
	Item item3(11);

	SafeSet<Item, ItemLess> set;

	ASSERT_EQ(set.Insert(item1), true);
	ASSERT_EQ(set.Size(), 1);
	ASSERT_EQ(set.Insert(item1), false);
	ASSERT_EQ(set.Size(), 1);
	ASSERT_EQ(set.Insert(item2), true);
	ASSERT_EQ(set.Size(), 2);
	ASSERT_EQ(set.Insert(item3), true);
	ASSERT_EQ(set.Size(), 3);
}


TEST(Test_ThreadSafeSet, Remove)
{
	Item item1(10);
	Item item2(2);
	Item item3(11);

	SafeSet<Item, ItemLess> set;
	set.Remove(item1);
	ASSERT_EQ(set.Size(), 0);

	set.Insert(item1);
	set.Insert(item2);
	set.Insert(item3);

	SafeSet<Item, ItemLess> set2 = set;
	ASSERT_EQ(set2.Size(), 3);

	set.Remove(item1);
	ASSERT_EQ(set.Size(), 2);
	set.Remove(item3);
	ASSERT_EQ(set.Size(), 1);
	set.Remove(item2);
	ASSERT_EQ(set.Size(), 0);
}

TEST(Test_ThreadSafeSet, Search)
{
	SafeSet<Item, ItemLess> set;

	#pragma omp parallel
	for (int i = 0; i < 10000; ++i)
	{
		Item item(i);
		set.Insert(item);
	}
	
	ASSERT_EQ(set.Search(10).Correct, true);
	ASSERT_EQ(set.Search(11).Correct, true);
	ASSERT_EQ(set.Search(2444).Correct, true);
	ASSERT_EQ(set.Search(107774).Correct, false);
}
