#include <gtest/gtest.h>

#include "Color.hpp"

using namespace midnight;

TEST(Color, DefaultConstruction)
{
	Color3F color;
	ASSERT_FLOAT_EQ(0.0f, color[0]);
	ASSERT_FLOAT_EQ(0.0f, color[1]);
	ASSERT_FLOAT_EQ(0.0f, color[2]);
}

TEST(Color, PseudoCopyConstruction)
{
	Color3F original;
	Color3F copy(original);
	ASSERT_FLOAT_EQ(0.0f, copy[0]);
	ASSERT_FLOAT_EQ(0.0f, copy[1]);
	ASSERT_FLOAT_EQ(0.0f, copy[2]);
}

TEST(Color, PseudoMoveConstruction)
{
	Color3F original;
	Color3F moved(std::move(original));
	ASSERT_FLOAT_EQ(0.0f, moved[0]);
	ASSERT_FLOAT_EQ(0.0f, moved[1]);
	ASSERT_FLOAT_EQ(0.0f, moved[2]);
}

TEST(Color, CopyAssignment)
{
	Color3F original;
	Color3F copy = original;
	ASSERT_FLOAT_EQ(0.0f, copy[0]);
	ASSERT_FLOAT_EQ(0.0f, copy[1]);
	ASSERT_FLOAT_EQ(0.0f, copy[2]);
}

TEST(Color, MoveAssignment)
{
	Color3F original;
	Color3F moved = std::move(original);
	ASSERT_FLOAT_EQ(0.0f, moved[0]);
	ASSERT_FLOAT_EQ(0.0f, moved[1]);
	ASSERT_FLOAT_EQ(0.0f, moved[2]);
}

TEST(Color, ParameterPackConstruction)
{
	Color3F color(1.0f, 2.0f, 3.0f);
	ASSERT_FLOAT_EQ(1.0f, color[0]);
	ASSERT_FLOAT_EQ(2.0f, color[1]);
	ASSERT_FLOAT_EQ(3.0f, color[2]);
}

TEST(Color, FreeUnaryOperations)
{
	Color3F color(100, -100, 0);
	color = -color;
	ASSERT_FLOAT_EQ(-100.0f, color[0]);
	ASSERT_FLOAT_EQ(100.0f, color[1]);
	ASSERT_FLOAT_EQ(0.0f, color[2]);
}
