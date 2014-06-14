#include <gtest/gtest.h>

#include "Tuple.hpp"

using namespace midnight;

TEST(Tuple, DefaultConstructor)
{
	Tuple3I tuple;
	ASSERT_EQ(0, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(0, tuple[2]);
}

TEST(Tuple, InitializerListConstructor)
{
	Tuple3I tuple {1, 2, 3};
}

TEST(Tuple, ParameterPackConstructor)
{
	Tuple3I tuple(1, 2, 3);
	ASSERT_EQ(1, tuple[0]);
	ASSERT_EQ(2, tuple[1]);
	ASSERT_EQ(3, tuple[2]);

	// Uncomment to test compile-time assertions
	// Tuple3I compileError0(1, 2, 3, 4); // Too many elements provided
	// Tuple3I compileError1(1, 2); // Too few elements provided
}

TEST(Tuple, Set)
{
	Tuple3I tuple;
	tuple.set(100, 100, 100);
	ASSERT_EQ(100, tuple[0]);
	ASSERT_EQ(100, tuple[1]);
	ASSERT_EQ(100, tuple[2]);
}

TEST(Tuple, FreeRelationalOperators)
{
	Tuple3I tuple0;
	Tuple3I tuple1;
	ASSERT_EQ(true, tuple0 == tuple1);
	ASSERT_EQ(false, tuple0 != tuple1);
	ASSERT_EQ(false, tuple0 < tuple1);
	ASSERT_EQ(false, tuple0 > tuple1);
	ASSERT_EQ(true, tuple0 <= tuple1);
	ASSERT_EQ(true, tuple0 >= tuple1);

	tuple1.set(1, 1, 1);
	ASSERT_EQ(false, tuple0 == tuple1);
	ASSERT_EQ(true, tuple0 != tuple1);
	ASSERT_EQ(true, tuple0 < tuple1);
	ASSERT_EQ(false, tuple0 > tuple1);
	ASSERT_EQ(true, tuple0 <= tuple1);
	ASSERT_EQ(false, tuple0 >= tuple1);
}

TEST(Tuple, FreeUnaryOperators)
{
	Tuple3I tuple(1.0f, 2.0f, 3.0f);
	tuple = -tuple;
	ASSERT_EQ(-1, tuple[0]);
	ASSERT_EQ(-2, tuple[1]);
	ASSERT_EQ(-3, tuple[2]);
}

TEST(Tuple, FreeGetFunction)
{
	Tuple3I tuple(2, 3, 4);

	ASSERT_EQ(2, get<0>(std::move(tuple)));
	ASSERT_EQ(3, get<1>(std::move(tuple)));
	ASSERT_EQ(4, get<2>(std::move(tuple)));

	ASSERT_EQ(2, get<0>(tuple));
	ASSERT_EQ(3, get<1>(tuple));
	ASSERT_EQ(4, get<2>(tuple));
}

TEST(Tuple, Iterators)
{
	Tuple3I tuple(0, 1, 2);
	Tuple3I::iterator iter0 = tuple.begin();
	ASSERT_EQ(0, *iter0);
	ASSERT_EQ(1, *(iter0 + 1));
	ASSERT_EQ(2, *(iter0 + 2));

	Tuple3I::const_iterator iter1 = tuple.begin();
	ASSERT_EQ(0, *iter1);
	ASSERT_EQ(1, *(iter1 + 1));
	ASSERT_EQ(2, *(iter1 + 2));

	Tuple3I::reverse_iterator iter2 = tuple.rbegin();
	ASSERT_EQ(2, *iter2);
	ASSERT_EQ(1, *(iter2 + 1));
	ASSERT_EQ(0, *(iter2 + 2));

	Tuple3I::const_reverse_iterator iter3 = tuple.rbegin();
	ASSERT_EQ(2, *iter3);
	ASSERT_EQ(1, *(iter3 + 1));
	ASSERT_EQ(0, *(iter3 + 2));
}

TEST(Tuple, Size)
{
	Tuple3I tuple0;
	ASSERT_EQ(3, tuple0.size());
	Tuple4F tuple1;
	ASSERT_EQ(4, tuple1.size());
}

TEST(Tuple, ScalarMultiplication)
{
	Tuple3I tuple(1, 2, 3);
	tuple *= 3;
	ASSERT_EQ(3, tuple[0]);
	ASSERT_EQ(6, tuple[1]);
	ASSERT_EQ(9, tuple[2]);

	tuple.set(-100, 0, 1000);
	tuple *= 5;
	ASSERT_EQ(-500, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(5000, tuple[2]);
}

TEST(Tuple, TupleMultiplication)
{
	Tuple3I tuple(1, 2, 3);
	tuple *= Tuple3I(1, 2, 3);
	ASSERT_EQ(1, tuple[0]);
	ASSERT_EQ(4, tuple[1]);
	ASSERT_EQ(9, tuple[2]);

	tuple.set(-100, 0, 100);
	tuple *= Tuple3I(-1, -1, -1);
	ASSERT_EQ(100, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(-100, tuple[2]);
}

TEST(Tuple, ScalarAddition)
{
	Tuple3I tuple(1, 2, 3);
	tuple += 100;
	ASSERT_EQ(101, tuple[0]);
	ASSERT_EQ(102, tuple[1]);
	ASSERT_EQ(103, tuple[2]);

	tuple.set(-100, -100, -100);
	tuple += -100;
	ASSERT_EQ(-200, tuple[0]);
	ASSERT_EQ(-200, tuple[1]);
	ASSERT_EQ(-200, tuple[2]);

}

TEST(Tuple, TupleAddition)
{
	Tuple3I tuple(1, 2, 3);
	tuple += Tuple3I(4, 5, 6);
	ASSERT_EQ(5, tuple[0]);
	ASSERT_EQ(7, tuple[1]);
	ASSERT_EQ(9, tuple[2]);

	tuple.set(-1, -2, -3);
	tuple += Tuple3I(-4, -5, -6);
	ASSERT_EQ(-5, tuple[0]);
	ASSERT_EQ(-7, tuple[1]);
	ASSERT_EQ(-9, tuple[2]);
}

TEST(Tuple, ScalarSubtraction)
{
	Tuple3I tuple(1, 2, 3);
	tuple -= 1;
	ASSERT_EQ(0, tuple[0]);
	ASSERT_EQ(1, tuple[1]);
	ASSERT_EQ(2, tuple[2]);

	tuple.set(-1, -2, -3);
	tuple -= -1;
	ASSERT_EQ(0, tuple[0]);
	ASSERT_EQ(-1, tuple[1]);
	ASSERT_EQ(-2, tuple[2]);
}

TEST(Tuple, TupleSubtraction)
{
	Tuple3I tuple(1, 2, 3);
	tuple -= Tuple3I(1, 2, 3);
	ASSERT_EQ(0, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(0, tuple[2]);

	tuple.set(-100, 0, 100);
	tuple -= Tuple3I(100, 0, -100);
	ASSERT_EQ(-200, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(200, tuple[2]);
}

TEST(Tuple, ClampMin)
{
	Tuple3I tuple(-100, 0, 100);
	tuple.clampMin(-5);
	ASSERT_EQ(-5, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(100, tuple[2]);
}

TEST(Tuple, Clamp)
{
	Tuple3I tuple(-100, 0, 100);
	tuple.clamp(-5, 5);
	ASSERT_EQ(-5, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(5, tuple[2]);
}

TEST(Tuple, ClampMax)
{
	Tuple3I tuple(-100, 0, 100);
	tuple.clampMax(5);
	ASSERT_EQ(-100, tuple[0]);
	ASSERT_EQ(0, tuple[1]);
	ASSERT_EQ(5, tuple[2]);
}

