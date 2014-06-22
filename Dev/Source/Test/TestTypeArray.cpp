#include "gtest/gtest.h"
#include "FTypeArray.h"

#include <memory>

using namespace FRE::Utils;

struct TypeGetter
{
	typedef const std::type_info & Type;

	template <typename T>
	static Type GetType() { return typeid(T); }
};

TEST(Test_TypeArray, AddRemoveValues)
{
	FTypedArray<TypeGetter> typedArr;
	typedArr.Add(1);
	typedArr.Add(0.1f);

	typedArr.Remove(0);
	typedArr.Remove(1);

	auto i1 = typedArr.Add((int)12);
	auto i2 = typedArr.Add((float)0.1f);

	EXPECT_EQ(i1 < 2, true);
	EXPECT_EQ(i2 < 2, true);

	EXPECT_EQ(typedArr.Get<float>(i2).first, true);
	EXPECT_EQ(typedArr.Get<float>(i2).second, 0.1f);
	EXPECT_EQ(typedArr.Get<float>(i1).first, false);

	EXPECT_EQ(typedArr.Get<int>(i2).first, false);
	EXPECT_EQ(typedArr.Get<int>(i1).first, true);
	EXPECT_EQ(typedArr.Get<int>(i1).second, 12);
}