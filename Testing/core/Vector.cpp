#include <gtest/gtest.h>

#include "constexpr_math.hpp"
#include "Vector.hpp"
using namespace midnight;
TEST(Vector, DefaultConstruction)
{
	Vector3F vector;
	ASSERT_FLOAT_EQ(0.0f, vector[0]);
	ASSERT_FLOAT_EQ(0.0f, vector[1]);
	ASSERT_FLOAT_EQ(0.0f, vector[2]);
}

TEST(Vector, ParameterPackConstruction)
{
	Vector3F vector(1.0f, 2.0f, 3.0f);
	ASSERT_FLOAT_EQ(1.0f, vector[0]);
	ASSERT_FLOAT_EQ(2.0f, vector[1]);
	ASSERT_FLOAT_EQ(3.0f, vector[2]);
}

TEST(Vector, FreeUnaryOperations)
{
	Vector3F vector(100, -100, 0);
	vector = -vector;
	ASSERT_FLOAT_EQ(-100.0f, vector[0]);
	ASSERT_FLOAT_EQ(100.0f, vector[1]);
	ASSERT_FLOAT_EQ(0.0f, vector[2]);
}

TEST(Vector, FreeAngles)
{
	Vector3F v0(1.0f, 0.0f, 0.0f); // Pointing right along x-axis
	Vector3F v1(0.0f, 1.0f, 0.0f); // Pointing up along y-axis
	ASSERT_FLOAT_EQ(90.0f, toDegrees(angleBetween(v0, v1)));
}

TEST(Vector, MemberAngles)
{
	Vector3F v0(1.0f, 0.0f, 0.0f); // Pointing right along x-axis
	Vector3F v1(0.0f, 1.0f, 0.0f); // Pointing up along y-axis
	ASSERT_FLOAT_EQ(90.0f, toDegrees(v0.angleBetween(v1)));
}

TEST(Vector, Length)
{
	Vector2F v(3.0f, 4.0f);
	ASSERT_FLOAT_EQ(5.0f, v.length());
	v = -v;
	ASSERT_FLOAT_EQ(5.0f, v.length());
}

TEST(Vector, Normalization)
{
	Vector3F v(1.0f, 2.0f, 3.0f);
	v.normalize();
	ASSERT_FLOAT_EQ(1.0f, v.length());
}

TEST(Vector, FreeDotProduct)
{
	Vector3F v0(1, 2, 3);
	Vector3F v1(1, 2, 3);
	ASSERT_FLOAT_EQ(14.0f, dot(v0, v1));
}

TEST(Vector, MemberDotProduct)
{
	Vector3F v0(1, 2, 3);
	Vector3F v1(1, 2, 3);
	ASSERT_FLOAT_EQ(14.0f, v0.dot(v1));
}

TEST(Vector, FreeCrossProduct)
{
	Vector3F vector = cross(Vector3F(1, 2, 3), Vector3F(2, 3, 4));
	///-1i +2j -1k
	ASSERT_FLOAT_EQ(-1.0f, vector[0]);
	ASSERT_FLOAT_EQ(2.0f, vector[1]);
	ASSERT_FLOAT_EQ(-1.0f, vector[2]);
}

TEST(Vector, MemberCrossProduct)
{
	Vector3F vector = Vector3F(1, 2, 3).cross(Vector3F(2, 3, 4));
	///-1i +2j -1k
	ASSERT_FLOAT_EQ(-1.0f, vector[0]);
	ASSERT_FLOAT_EQ(2.0f, vector[1]);
	ASSERT_FLOAT_EQ(-1.0f, vector[2]);
}

/*
void Cross()
{
	
}
 */