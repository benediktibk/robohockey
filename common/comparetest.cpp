#include "common/comparetest.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace std;

void CompareTest::isFuzzyEqual_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyEqual()
{
	Compare compare(0.2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(2.0,2.1));
}

void CompareTest::isFuzzyEqual_twoCompletelyEqualVectors_true()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two = one;

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoNearlyEqualVectors_true()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two.push_back(4);
	two.push_back(3.1);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoVectorsWithDifferentSize_false()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two.push_back(4);
	two.push_back(3.1);
	two.push_back(1);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoDifferentVectors_false()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two.push_back(4);
	two.push_back(2);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
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

void CompareTest::isStrictFuzzyGreater_onlyLittleBitGreater_false()
{
	Compare compare(0.1);

	CPPUNIT_ASSERT(!compare.isStrictFuzzyGreater(2.05, 2));
}
