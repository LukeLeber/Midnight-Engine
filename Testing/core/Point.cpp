#include <gtest/gtest.h>

#include "Point.hpp"
using namespace midnight;
TEST(Point, DefaultConstruction)
{
	Point3F point;
	ASSERT_FLOAT_EQ(0.0f, point[0]);
	ASSERT_FLOAT_EQ(0.0f, point[1]);
	ASSERT_FLOAT_EQ(0.0f, point[2]);
}

TEST(Point, ParameterPackConstruction)
{
	Point3F point(1.0f, 2.0f, 3.0f);
	ASSERT_FLOAT_EQ(1.0f, point[0]);
	ASSERT_FLOAT_EQ(2.0f, point[1]);
	ASSERT_FLOAT_EQ(3.0f, point[2]);
}

TEST(Point, FreeUnaryOperations)
{
	Point3F point(1.0f, 2.0f, 3.0f);
	point = -point;
	ASSERT_FLOAT_EQ(-1.0f, point[0]);
	ASSERT_FLOAT_EQ(-2.0f, point[1]);
	ASSERT_FLOAT_EQ(-3.0f, point[2]);
}

TEST(Point, FreeDistance)
{
	Point2F p0;
	Point2F p1(3.0f, 4.0f);
	ASSERT_FLOAT_EQ(5.0f, p0.distanceFrom(p1));
}

TEST(Point, MemberDistance)
{
	Point2F p0;
	Point2F p1(3.0f, 4.0f);
	ASSERT_FLOAT_EQ(5.0f, distanceBetween(p0, p1));
}
