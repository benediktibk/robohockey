#ifndef ROBOHOCKEY_COMMON_DISCRETEFUNCTIONTEST_H
#define ROBOHOCKEY_COMMON_DISCRETEFUNCTIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class DiscreteFunctionTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(DiscreteFunctionTest);
		CPPUNIT_TEST(constructor_1And5_3IsInRange);
		CPPUNIT_TEST(constructor_minus3And4_valueAt1Is0);
		CPPUNIT_TEST(isWithinRange_startAtMinus3AndMinus2_true);
		CPPUNIT_TEST(isWithinRange_startAtMinus3AndMinus3_true);
		CPPUNIT_TEST(isWithinRange_startAtMinus3AndMinus4_false);
		CPPUNIT_TEST(isWithinRange_endAt5And5_true);
		CPPUNIT_TEST(isWithinRange_endAt5And6_false);
		CPPUNIT_TEST(setValue_4At3_valueAt3Is4);
		CPPUNIT_TEST(setValue_3AtMinus1_valueAtMinus1Is3);
		CPPUNIT_TEST(suppressNoiseHeavy_sineWithNoise_nearlySine);
		CPPUNIT_TEST(differentiate_sine_cosine);
		CPPUNIT_TEST(differentiate_xToThe3_threeTimesXToThe2);
		CPPUNIT_TEST(operatorMultiplyAndAssign_threeValues3With2_valuesAre6);
		CPPUNIT_TEST(getPositionsWithValuesAbove_twoValuesAbove_bothPositionsContainedInResult);
		CPPUNIT_TEST(getPositionsWithValuesBelow_oneValueBelow_positionContainedInResult);
		CPPUNIT_TEST(getMinimumInRange_onlyOneValue_onlyValue);
		CPPUNIT_TEST(getMinimumInRange_severalValues_smallestValue);
		CPPUNIT_TEST(getMinimumInRange_rangeIsWholeFunction_totalMinimum);
		CPPUNIT_TEST(getMeanValueInRange_severalValues_correctResult);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_1And5_3IsInRange();
		void constructor_minus3And4_valueAt1Is0();
		void isWithinRange_startAtMinus3AndMinus2_true();
		void isWithinRange_startAtMinus3AndMinus3_true();
		void isWithinRange_startAtMinus3AndMinus4_false();
		void isWithinRange_endAt5And5_true();
		void isWithinRange_endAt5And6_false();
		void setValue_4At3_valueAt3Is4();
		void setValue_3AtMinus1_valueAtMinus1Is3();
		void suppressNoiseHeavy_sineWithNoise_nearlySine();
		void differentiate_sine_cosine();
		void differentiate_xToThe3_threeTimesXToThe2();
		void operatorMultiplyAndAssign_threeValues3With2_valuesAre6();
		void getPositionsWithValuesAbove_twoValuesAbove_bothPositionsContainedInResult();
		void getPositionsWithValuesBelow_oneValueBelow_positionContainedInResult();
		void getMinimumInRange_onlyOneValue_onlyValue();
		void getMinimumInRange_severalValues_smallestValue();
		void getMinimumInRange_rangeIsWholeFunction_totalMinimum();
		void getMeanValueInRange_severalValues_correctResult();
	};
}
}

#endif
