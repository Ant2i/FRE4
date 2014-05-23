#include "gtest/gtest.h"
#include "FMath.h"

using namespace FRE::Math;

TEST(Test_Math, VectorElementGetSet)
{
	Vector4f_t v;
	v[0] = 1.0f;
	v[1] = 2.0f;
	v[2] = 3.0f;
	v[3] = 4.0f;

	ASSERT_EQ(v[0], 1.0f);
	ASSERT_EQ(v[1], 2.0f);
	ASSERT_EQ(v[2], 3.0f);
	ASSERT_EQ(v[3], 4.0f);
}

TEST(Test_Math, VectorAdd)
{
	Vector4f_t v1(1.0f, 2.0f, 4.0f, 5.0);
	Vector4f_t v2(3.0f, 34.0f, 3.0f, 33.0);
	Vector4f_t v = VecAdd(v1, v2);

	ASSERT_EQ(v[0], 4.0f);
	ASSERT_EQ(v[1], 36.0f);
	ASSERT_EQ(v[2], 7.0f);
	ASSERT_EQ(v[3], 38.0f);
}