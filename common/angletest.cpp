#include "common/angletest.h"
#include "common/angle.h"
#include "common/point.h"
#include <math.h>

using namespace RoboHockey::Common;

void AngleTest::constructor_empty_valueIs0()
{
	Angle angle;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_2_valueIs2()
{
	Angle angle(2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_minus2_valueIsMinus2()
{
	Angle angle(-2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-2, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_10_valueIsMinus256()
{
	Angle angle(10);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.56637061435917295385, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_from0And0To1And0And0And1_valueIsPiHalf()
{
	Point source(0, 0);
	Point targetOne(1, 0);
	Point targetTwo(0, 1);

	Angle angle(source, targetOne, targetTwo);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI/2, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_from1And1To2And0And0And1_valueIs3PiQuarters()
{
	Point source(1, 1);
	Point targetOne(2, 0);
	Point targetTwo(0, 1);

	Angle angle(source, targetOne, targetTwo);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3*M_PI/4, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_threePointsAndOneTargetEqualToSource_0()
{
	Point source(1, 1);
	Point targetOne(1, 1);
	Point targetTwo(0, 1);

	Angle angle(source, targetOne, targetTwo);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_targetsEqual_0()
{
	Point source(0, 0);
	Point targetOne(1, 1);
	Point targetTwo(1, 1);

	Angle angle(source, targetOne, targetTwo);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::constructor_startAt1And3EndAtMinus2And1_correctResult()
{
	Point start(1, 3);
	Point end(-2, 1);

	Angle angle(start, end);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.55359, angle.getValueBetweenMinusPiAndPi(), 0.001);
}

void AngleTest::getValueBetweenZeroAndTwoPi_negativeValue_correctPositiveValue()
{
	Angle angle(-3);

	double valueShouldBe = -3 + 2*M_PI;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(valueShouldBe, angle.getValueBetweenZeroAndTwoPi(), 0.00001);
}

void AngleTest::getHalfRotation_empty_valueIsPi()
{
	Angle angle = Angle::getHalfRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::getQuarterRotation_empty_valueIsPiHalf()
{
	Angle angle = Angle::getQuarterRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI/2, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::getFullRotation_empty_valueIs0()
{
	Angle angle = Angle::getFullRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::operatorPlus_3And5_valueIsCorrect()
{
	Angle angle = Angle(3) + Angle(5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.71681469282041352307, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::operatorMinus_Minus3And4_valueIsCorrect()
{
	Angle angle = Angle(-3) - Angle(4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.71681469282041352307, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::operatorMultiply_2And3_valueIsCorrect()
{
	Angle angle(2);

	Angle result = angle*3;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.28318530717958647693, result.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::operatorDivide_3And2_valueIsCorrect()
{
	Angle angle(3);

	Angle result = angle/2;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.5, result.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::operatorMinus_twoAnglesConstructedFromPoints_valueIsNegative()
{
	Angle one(Point(4, 7), Point(3, 3));
	Angle two(Point(4, 7), Point(6, 2));

	Angle result = one - two;

	CPPUNIT_ASSERT(result.getValueBetweenMinusPiAndPi() < 0);
}

void AngleTest::abs_1_valueIs1()
{
	Angle angle(1);

	angle.abs();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::abs_minus1_valueIs1()
{
	Angle angle(-1);

	angle.abs();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::getEighthRotation_empty_valueIsPiQuarter()
{
	Angle angle = Angle::getEighthRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI/4, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}

void AngleTest::getThreeQuarterRotation_empty_valueIsThreeHalfPi()
{
	Angle angle = Angle::getThreeQuarterRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-M_PI/2, angle.getValueBetweenMinusPiAndPi(), 0.00001);
}
