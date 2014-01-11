#ifndef ROBOHOCKEY_COMMON_COMPARETEST_H
#define ROBOHOCKEY_COMMON_COMPARETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class CompareTest :
		public CPPUNIT_NS::TestFixture
	{
	CPPUNIT_TEST_SUITE(CompareTest);
	CPPUNIT_TEST(isFuzzyEqual_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyEqual);
	CPPUNIT_TEST(isFuzzyEqual_twoCompletelyEqualVectors_true);
	CPPUNIT_TEST(isFuzzyEqual_twoNearlyEqualVectors_true);
	CPPUNIT_TEST(isFuzzyEqual_twoVectorsWithDifferentSize_false);
	CPPUNIT_TEST(isFuzzyEqual_twoDifferentVectors_false);
	CPPUNIT_TEST(isFuzzyGreater_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyGreater);
	CPPUNIT_TEST(isFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzySmaller);
	CPPUNIT_TEST(isStrictFuzzyGreater_twoPointOneAndTwoAndEpsilonZeroPointZeroFife_resultIsStrictFuzzyGreater);
	CPPUNIT_TEST(isStrictFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointZeroFife_resultIsStrictFuzzySmaller);
	CPPUNIT_TEST(isStrictFuzzyGreater_onlyLittleBitGreater_false);
	CPPUNIT_TEST_SUITE_END();

	private:
		void isFuzzyEqual_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyEqual();
		void isFuzzyEqual_twoCompletelyEqualVectors_true();
		void isFuzzyEqual_twoNearlyEqualVectors_true();
		void isFuzzyEqual_twoVectorsWithDifferentSize_false();
		void isFuzzyEqual_twoDifferentVectors_false();
		void isFuzzyGreater_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyGreater();
		void isFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzySmaller();
		void isStrictFuzzyGreater_twoPointOneAndTwoAndEpsilonZeroPointZeroFife_resultIsStrictFuzzyGreater();
		void isStrictFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointZeroFife_resultIsStrictFuzzySmaller();
		void isStrictFuzzyGreater_onlyLittleBitGreater_false();
	};
}
}

#endif
