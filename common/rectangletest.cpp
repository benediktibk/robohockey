#include "common/rectangletest.h"
#include "common/rectangle.h"
#include "common/compare.h"
#include "common/circle.h"

using namespace RoboHockey::Common;

RectangleTest::RectangleTest() :
	m_compare(0)
{ }

void RectangleTest::setUp()
{
	delete m_compare;
	m_compare = new Compare(0.01);
}

void RectangleTest::tearDown()
{
	delete m_compare;
	m_compare = 0;
}

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

void RectangleTest::isInside_tooMuchLeft_false()
{
	Rectangle rectangle(Point(0, 1), Point(3, 5));

	CPPUNIT_ASSERT(!rectangle.isInside(Point(-1, 2), *m_compare));
}

void RectangleTest::isInside_tooMuchRight_false()
{
	Rectangle rectangle(Point(0, 1), Point(3, 5));

	CPPUNIT_ASSERT(!rectangle.isInside(Point(4, 2), *m_compare));
}

void RectangleTest::isInside_tooMuchDown_false()
{
	Rectangle rectangle(Point(0, 1), Point(3, 5));

	CPPUNIT_ASSERT(!rectangle.isInside(Point(2, -2), *m_compare));
}

void RectangleTest::isInside_tooMuchUp_false()
{
	Rectangle rectangle(Point(0, 1), Point(3, 5));

	CPPUNIT_ASSERT(!rectangle.isInside(Point(2, 9), *m_compare));
}

void RectangleTest::isInside_inside_true()
{
	Rectangle rectangle(Point(0, 1), Point(3, 5));

	CPPUNIT_ASSERT(rectangle.isInside(Point(2, 2), *m_compare));
}

void RectangleTest::getWidth_4And5AsLeftLowerAnd7And6AsRightUpper_3()
{
	Rectangle rectangle(Point(4, 5), Point(7, 6));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, rectangle.getWidth(), 0.00001);
}

void RectangleTest::getHeight_4And5AsLeftLowerAnd7And6AsRightUpper_1()
{
	Rectangle rectangle(Point(4, 5), Point(7, 6));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, rectangle.getHeight(), 0.00001);
}

void RectangleTest::overlaps_rectangleInside_true()
{
	Rectangle one(Point(0, 0), Point(5, 5));
	Rectangle two(Point(1, 1), Point(4, 4));

	CPPUNIT_ASSERT(one.overlaps(two, *m_compare));
}

void RectangleTest::overlaps_ownRectangleInsideOtherOne_true()
{
	Rectangle one(Point(1, 1), Point(4, 4));
	Rectangle two(Point(0, 0), Point(5, 5));

	CPPUNIT_ASSERT(one.overlaps(two, *m_compare));
}

void RectangleTest::overlaps_overlappingHorizontal_true()
{
	Rectangle one(Point(0, 0), Point(5, 5));
	Rectangle two(Point(-4, 2), Point(5, 3));

	CPPUNIT_ASSERT(one.overlaps(two, *m_compare));
}

void RectangleTest::overlaps_overlappingVertical_true()
{
	Rectangle one(Point(0, 0), Point(5, 5));
	Rectangle two(Point(1, -2), Point(4, 8));

	CPPUNIT_ASSERT(one.overlaps(two, *m_compare));
}

void RectangleTest::overlaps_notOverlapping_false()
{
	Rectangle one(Point(0, 0), Point(5, 5));
	Rectangle two(Point(10, 20), Point(40, 80));

	CPPUNIT_ASSERT(!one.overlaps(two, *m_compare));
}

void RectangleTest::overlapsApproximately_realOverlap_true()
{
	Rectangle rectangle(Point(0, 0), Point(10, 10));
	Circle circle(Point(1, 1), 2);

	CPPUNIT_ASSERT(rectangle.overlapsApproximately(circle, *m_compare));
}

void RectangleTest::overlapsApproximately_onlyOverlappingWithBoundingRectangle_true()
{
	Rectangle rectangle(Point(0, 0), Point(10, 10));
	Circle circle(Point(-0.8, -0.8), 2);

	CPPUNIT_ASSERT(rectangle.overlapsApproximately(circle, *m_compare));
}

void RectangleTest::overlapsApproximately_notOverlapping_false()
{
	Rectangle rectangle(Point(0, 0), Point(10, 10));
	Circle circle(Point(-2, -2), 1);

	CPPUNIT_ASSERT(!rectangle.overlapsApproximately(circle, *m_compare));
}
