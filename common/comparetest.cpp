#include "common/comparetest.h"
#include "common/compare.h"

using namespace RoboHockey::Common;

void CompareTest::isFuzzyEqual_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyEqual()
{
	Compare compare(0.2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(2.0,2.1));
}

void CompareTest::isFuzzyGreater_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyGreater()
{
	Compare compare(0.2);

	CPPUNIT_ASSERT(compare.isFuzzyGreater(2.0,2.1));
}

void CompareTest::isFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzySmaller()
{
	Compare compare(0.2);

	CPPUNIT_ASSERT(compare.isFuzzySmaller(2.0,2.1));
}

void CompareTest::isStrictFuzzyGreater_twoPointOneAndTwoAndEpsilonZeroPointZeroFife_resultIsStrictFuzzyGreater()
{
	Compare compare(0.05);

	CPPUNIT_ASSERT(compare.isStrictFuzzyGreater(2.1,2.0));
}

void CompareTest::isStrictFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointZeroFife_resultIsStrictFuzzySmaller()
{
	Compare compare(0.05);

	CPPUNIT_ASSERT(compare.isStrictFuzzySmaller(2.0,2.1));
}
