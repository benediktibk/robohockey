#include "common/rectangletest.h"
#include "common/rectangle.h"

using namespace RoboHockey::Common;

void RectangleTest::constructor_4And5AsOneAnd9And8AsTwo_leftLowerIs4And5()
{
	Point one(4, 5);
	Point two(9, 8);

	Rectangle rectangle(one, two);

	CPPUNIT_ASSERT_EQUAL(one, rectangle.getLeftLower());
}

void RectangleTest::constructor_4And5AsOneAnd9And8AsTwo_rightUpperIs9And8()
{
	Point one(4, 5);
	Point two(9, 8);

	Rectangle rectangle(one, two);

	CPPUNIT_ASSERT_EQUAL(two, rectangle.getRightUpper());
}

void RectangleTest::constructor_9And8AsOneAnd4And5AsTwo_leftLowerIs4And5()
{
	Point one(9, 8);
	Point two(4, 5);

	Rectangle rectangle(one, two);

	CPPUNIT_ASSERT_EQUAL(two, rectangle.getLeftLower());
}

void RectangleTest::constructor_9And8AsOneAnd4And5AsTwo_rightUpperIs9And8()
{
	Point one(9, 8);
	Point two(4, 5);

	Rectangle rectangle(one, two);

	CPPUNIT_ASSERT_EQUAL(one, rectangle.getRightUpper());
}

void RectangleTest::constructor_1And5AsOneAnd4And1AsTwo_leftLowerIs1And1()
{
	Point one(1, 5);
	Point two(4, 1);

	Rectangle rectangle(one, two);

	CPPUNIT_ASSERT_EQUAL(Point(1, 1), rectangle.getLeftLower());
}

void RectangleTest::constructor_1And5AsOneAnd4And1AsTwo_rightUpperIs4And5()
{
	Point one(1, 5);
	Point two(4, 1);

	Rectangle rectangle(one, two);

	CPPUNIT_ASSERT_EQUAL(Point(4, 5), rectangle.getRightUpper());
}
