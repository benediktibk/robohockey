#include "common/angletest.h"
#include "common/angle.h"
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
