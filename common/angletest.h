#ifndef ROBOHOCKEY_COMMON_ANGLETEST_H
#define ROBOHOCKEY_COMMON_ANGLETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class AngleTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(AngleTest);
		CPPUNIT_TEST(constructor_empty_valueIs0);
		CPPUNIT_TEST(constructor_2_valueIs2);
		CPPUNIT_TEST(constructor_minus2_valueIsMinus2);
		CPPUNIT_TEST(constructor_10_valueIsMinus256);
		CPPUNIT_TEST(constructor_from0And0To1And0And0And1_valueIsPiHalf);
		CPPUNIT_TEST(constructor_from1And1To2And0And0And1_valueIs3PiQuarters);
		CPPUNIT_TEST(constructor_threePointsAndOneTargetEqualToSource_0);
		CPPUNIT_TEST(constructor_targetsEqual_0);
		CPPUNIT_TEST(getValueBetweenZeroAndTwoPi_negativeValue_correctPositiveValue);
		CPPUNIT_TEST(getHalfRotation_empty_valueIsPi);
		CPPUNIT_TEST(getQuarterRotation_empty_valueIsPiHalf);
		CPPUNIT_TEST(getFullRotation_empty_valueIs0);
		CPPUNIT_TEST(operatorPlus_3And5_valueIsCorrect);
		CPPUNIT_TEST(operatorMinus_Minus3And4_valueIsCorrect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_valueIs0();
		void constructor_2_valueIs2();
		void constructor_minus2_valueIsMinus2();
		void constructor_10_valueIsMinus256();
		void constructor_from0And0To1And0And0And1_valueIsPiHalf();
		void constructor_from1And1To2And0And0And1_valueIs3PiQuarters();
		void constructor_threePointsAndOneTargetEqualToSource_0();
		void constructor_targetsEqual_0();
		void getValueBetweenZeroAndTwoPi_negativeValue_correctPositiveValue();
		void getHalfRotation_empty_valueIsPi();
		void getQuarterRotation_empty_valueIsPiHalf();
		void getFullRotation_empty_valueIs0();
		void operatorPlus_3And5_valueIsCorrect();
		void operatorMinus_Minus3And4_valueIsCorrect();
	};
}
}

#endif
