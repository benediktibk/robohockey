#include "common/discretefunctiontest.h"
#include "common/discretefunction.h"
#include "common/compare.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>

using namespace RoboHockey::Common;
using namespace std;

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

void DiscreteFunctionTest::suppressNoise_sineWithNoise_nearlySine()
{
	const int n = 100;
	srand(0);
	DiscreteFunction function(0, n);
	DiscreteFunction functionShouldBe(0, n);
	function.setValue(1, sin(1.0/n*M_PI*2));
	functionShouldBe.setValue(1, sin(1.0/n*M_PI*2));
	for (int i = 2; i < n - 1; ++i)
	{
		double x = static_cast<double>(i)/n*M_PI*2;
		double exactValue = sin(x);
		double noise = static_cast<double>(rand()%1000)/9000;
		double valueWithNoise = exactValue + noise;
		function.setValue(i, valueWithNoise);
		functionShouldBe.setValue(i, exactValue);
	}
	function.setValue(n - 1, sin((n - 1.0)/n*M_PI*2));
	functionShouldBe.setValue(n - 1, sin((n - 1.0)/n*M_PI*2));
	Compare compare(0.1);
	CPPUNIT_ASSERT(!DiscreteFunction::compareValues(compare, function, functionShouldBe));

	function.suppressNoise();

	CPPUNIT_ASSERT(DiscreteFunction::compareValues(compare, function, functionShouldBe));
}

void DiscreteFunctionTest::differentiate_sine_cosine()
{
	const int n = 100;
	const double rangeEnd = M_PI*2;
	DiscreteFunction function(0, n);
	DiscreteFunction functionShouldBe(0, n);
	functionShouldBe.setValue(0, 1);
	for (int i = 1; i < n; ++i)
	{
		double x = static_cast<double>(i)/n*rangeEnd;
		function.setValue(i, sin(x));
		functionShouldBe.setValue(i, cos(x));
	}
	functionShouldBe.setValue(n, 1);

	function.differentiate(rangeEnd/n);

	Compare compare(0.01);
	function.setValue(0, 1);
	function.setValue(n, 1);
	CPPUNIT_ASSERT(DiscreteFunction::compareValues(compare, function, functionShouldBe));
}

void DiscreteFunctionTest::differentiate_xToThe3_threeTimesXToThe2()
{
	const int n = 100;
	const double rangeEnd = 2;
	DiscreteFunction function(0, n);
	DiscreteFunction functionShouldBe(0, n);
	for (int i = 0; i <= n; ++i)
	{
		double x = static_cast<double>(i)/n*rangeEnd;
		function.setValue(i, x*x*x);
		functionShouldBe.setValue(i, 3*x*x);
	}

	function.differentiate(rangeEnd/n);

	Compare compare(0.1);
	function.setValue(0, 0);
	function.setValue(n, 3*2*2);
	CPPUNIT_ASSERT(DiscreteFunction::compareValues(compare, function, functionShouldBe));
}

void DiscreteFunctionTest::operatorMultiplyAndAssign_threeValues3With2_valuesAre6()
{
	DiscreteFunction function(0, 2);
	function.setValue(0, 3);
	function.setValue(1, 3);
	function.setValue(2, 3);

	function *= 2;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, function.getValue(0), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, function.getValue(1), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, function.getValue(2), 0.00001);
}

void DiscreteFunctionTest::getPositionsWithValuesAbove_twoValuesAbove_bothPositionsContainedInResult()
{
	DiscreteFunction function(0, 5);
	function.setValue(2, 4);
	function.setValue(3, 1);
	function.setValue(5, 2);

	list<int> result = function.getPositionsWithValuesAbove(1);

	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
	CPPUNIT_ASSERT(count(result.begin(), result.end(), 2) == 1);
	CPPUNIT_ASSERT(count(result.begin(), result.end(), 5) == 1);
}

void DiscreteFunctionTest::getPositionsWithValuesBelow_oneValueBelow_positionContainedInResult()
{
	DiscreteFunction function(0, 5);
	function.setValue(2, 4);
	function.setValue(3, -1);
	function.setValue(5, 2);

	list<int> result = function.getPositionsWithValuesBelow(0);

	CPPUNIT_ASSERT_EQUAL((size_t)1, result.size());
	CPPUNIT_ASSERT(count(result.begin(), result.end(), 3) == 1);
}
