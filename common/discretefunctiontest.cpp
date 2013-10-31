#include "common/discretefunctiontest.h"
#include "common/discretefunction.h"

using namespace RoboHockey::Common;


void DiscreteFunctionTest::constructor_1And5_3IsInRange()
{
	DiscreteFunction function(1, 5);

	CPPUNIT_ASSERT(function.withinRange(3));
}

void DiscreteFunctionTest::constructor_minus3And4_valueAt1Is0()
{
	DiscreteFunction function(-3, 4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, function.getValue(1), 0.000001);
}

void DiscreteFunctionTest::isWithinRange_startAtMinus3AndMinus2_true()
{
	DiscreteFunction function(-3, 5);

	CPPUNIT_ASSERT(function.withinRange(-2));
}

void DiscreteFunctionTest::isWithinRange_startAtMinus3AndMinus3_true()
{
	DiscreteFunction function(-3, 5);

	CPPUNIT_ASSERT(function.withinRange(-3));
}

void DiscreteFunctionTest::isWithinRange_startAtMinus3AndMinus4_false()
{
	DiscreteFunction function(-3, 5);

	CPPUNIT_ASSERT(!function.withinRange(-4));
}

void DiscreteFunctionTest::isWithinRange_endAt5And5_true()
{
	DiscreteFunction function(-3, 5);

	CPPUNIT_ASSERT(function.withinRange(5));
}

void DiscreteFunctionTest::isWithinRange_endAt5And6_false()
{
	DiscreteFunction function(-3, 5);

	CPPUNIT_ASSERT(!function.withinRange(6));
}

void DiscreteFunctionTest::setValue_4At3_valueAt3Is4()
{
	DiscreteFunction function(-3, 5);

	function.setValue(3, 4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, function.getValue(3), 0.000001);
}

void DiscreteFunctionTest::setValue_3AtMinus1_valueAtMinus1Is3()
{
	DiscreteFunction function(-3, 5);

	function.setValue(-1, 3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, function.getValue(-1), 0.000001);
}

void DiscreteFunctionTest::suppressNoise_oneDisturbingPeak_correctResult()
{
	CPPUNIT_ASSERT(false);
}

void DiscreteFunctionTest::differentiate_someValues_correctResult()
{
	CPPUNIT_ASSERT(false);
}
