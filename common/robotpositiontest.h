#ifndef ROBOHOCKEY_COMMON_ROBOTPOSITIONTEST_H
#define ROBOHOCKEY_COMMON_ROBOTPOSITIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class RobotPositionTest:
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotPositionTest);
		CPPUNIT_TEST(constructor_empty_positionIs0And0);
		CPPUNIT_TEST(constructor_4And3_positionIs4And3);
		CPPUNIT_TEST(setPosition_5And6_positionIs5And6);
		CPPUNIT_TEST(streamOperator_3And2_32);
		CPPUNIT_TEST(operatorMultiply_3And6With2_6And12);
		CPPUNIT_TEST(operatorDivide_3And6With3_1And2);
		CPPUNIT_TEST(operatorAdd_4And3To5And1_9And4);
		CPPUNIT_TEST(operatorMinus_5And3From9And4_4And1);
		CPPUNIT_TEST(operatorMultpliyAndAssign_3And5With2_6And10);
		CPPUNIT_TEST(distanceTo_from4And5To8And2_5);
		CPPUNIT_TEST(constructor_empty_orientationIs0);
		CPPUNIT_TEST(constructor_orientationIsPi_orientationIsPi);
		CPPUNIT_TEST(setOrientation_3_orientationIs3);
		CPPUNIT_TEST(read_validString_correctValues);
		CPPUNIT_TEST(getRelativeOrientationTo_lookingUpAndTargetInFourthQuarter_correctValue);
		CPPUNIT_TEST_SUITE_END();

   private:
		void constructor_empty_positionIs0And0();
		void constructor_4And3_positionIs4And3();
		void setPosition_5And6_positionIs5And6();
		void streamOperator_3And2_32();
		void operatorMultiply_3And6With2_6And12();
		void operatorDivide_3And6With3_1And2();
		void operatorAdd_4And3To5And1_9And4();
		void operatorMinus_5And3From9And4_4And1();
		void operatorMultpliyAndAssign_3And5With2_6And10();
		void distanceTo_from4And5To8And2_5();
		void constructor_empty_orientationIs0();
		void constructor_orientationIsPi_orientationIsPi();
		void setOrientation_3_orientationIs3();
		void read_validString_correctValues();
		void getRelativeOrientationTo_lookingUpAndTargetInFourthQuarter_correctValue();
	};
}
}

#endif
