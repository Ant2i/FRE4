//#include "gtest/gtest.h"
//#include "Containers/FreIndexMemory.h"
//
//#include <memory>
//
//class Type
//{
//public:
//	Type(unsigned i) : I(i)
//	{
//
//	}
//
//	~Type()
//	{
//
//	}
//
//	unsigned I;
//};
//
//using namespace FRE::Utils;
//
//#define ELEM_COUNT 1000
//
//TEST(Test_IndexMemory, Add)
//{
//	{
//		IndexMemory<Type> m2;
//		m2.Insert(Type(2));
//	}
//
//	IndexMemory<Type> memory;
//	for (unsigned i = 0; i < ELEM_COUNT; ++i)
//		memory.Insert(Type(i));
//
//	EXPECT_EQ(memory.GetSize(), ELEM_COUNT);
//}
//
//TEST(Test_IndexMemory, Copy)
//{
//	IndexMemory<Type> memory;
//	for (unsigned i = 0; i < ELEM_COUNT; ++i)
//		memory.Insert(Type(i));
//
//	IndexMemory<Type> memoryCopy(memory);
//
//	EXPECT_EQ(memory.GetSize(), ELEM_COUNT);
//	EXPECT_EQ(memoryCopy.GetSize(), ELEM_COUNT);
//}
//
//TEST(Test_IndexMemory, Remove)
//{
//	IndexMemory<Type> memory;
//	for (unsigned i = 0; i < ELEM_COUNT; ++i)
//		memory.Insert(Type(i));
//
//	for (unsigned i = 0; i < ELEM_COUNT; ++i)
//		memory.Remove(i);
//
//	EXPECT_EQ(memory.GetSize(), 0);
//}