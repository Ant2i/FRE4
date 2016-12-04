//#include "gtest/gtest.h"
//#include "Containers/FreAnyTypeArray.h"
//
//#include <memory>
//
//using namespace FRE::Utils;
//
//struct TypeGetter
//{
//	typedef const std::type_info & Type;
//
//	template <typename T>
//	static Type GetType() { return typeid(T); }
//};
//
//TEST(Test_AnyTypeArray, TestValues)
//{
//	AnyTypeArray<TypeGetter> typeArr;
//	typeArr.Add(1);
//	typeArr.Add(0.1f);
//
//	typeArr.Remove(0);
//	typeArr.Remove(1);
//
//	auto i1 = typeArr.Add((int)12);
//	auto i2 = typeArr.Add((float)0.1f);
//
//	EXPECT_EQ(i1 < 2, true);
//	EXPECT_EQ(i2 < 2, true);
//
//	EXPECT_EQ(typeArr.Get<float>(i2).first, true);
//	EXPECT_EQ(typeArr.Get<float>(i2).second, 0.1f);
//	EXPECT_EQ(typeArr.Get<float>(i1).first, false);
//
//	EXPECT_EQ(typeArr.Get<int>(i2).first, false);
//	EXPECT_EQ(typeArr.Get<int>(i1).first, true);
//	EXPECT_EQ(typeArr.Get<int>(i1).second, 12);
//}
//
//TEST(Test_AnyTypeArray, AddRemoveValues)
//{
//	AnyTypeArray<TypeGetter> typeArr;
//
//	for (unsigned i = 0; i < 1000; ++i)
//		typeArr.Add(i);
//
//	for (unsigned i = 0; i < 1000; ++i)
//		typeArr.Remove(i);
//
//	EXPECT_EQ(11, 11);
//}