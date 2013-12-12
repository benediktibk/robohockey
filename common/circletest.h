#ifndef ROBOHOCKEY_COMMON_CIRCLETEST_H
#define ROBOHOCKEY_COMMON_CIRCLETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class CircleTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CircleTest);
		CPPUNIT_TEST(constructor_empty_diameterIs0);
		CPPUNIT_TEST(constructor_centerAndDiameter_centerIsCorrect);
		CPPUNIT_TEST(constructor_centerAndDiameter_diameterIsCorrect);
		CPPUNIT_TEST(setCenter_4And5_centerIs4And5);
		CPPUNIT_TEST(setDiameter_3_diameterIs3);
		CPPUNIT_TEST(getBoundingRectangle_validCircle_correctResult);
		CPPUNIT_TEST(getDistanceTo_euclideanDistance5AndDiameter2_4);
		CPPUNIT_TEST(overlapsWith_farAway_false);
		CPPUNIT_TEST(overlapsWith_secondOneInsideFirstOne_true);
		CPPUNIT_TEST(overlapsWith_firstOneInsideSecondOne_true);
		CPPUNIT_TEST(overlapsWith_touching_true);
		CPPUNIT_TEST(overlapsWith_crossingWithCenterOutside_true);
		CPPUNIT_TEST(overlapsWith_crossingWithCenterInside_true);
		CPPUNIT_TEST(overlapsWith_closeTogetherButTooSmallDiameters_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_diameterIs0();
		void constructor_centerAndDiameter_centerIsCorrect();
		void constructor_centerAndDiameter_diameterIsCorrect();
		void setCenter_4And5_centerIs4And5();
		void setDiameter_3_diameterIs3();
		void getBoundingRectangle_validCircle_correctResult();
		void getDistanceTo_euclideanDistance5AndDiameter2_4();
		void overlapsWith_farAway_false();
		void overlapsWith_secondOneInsideFirstOne_true();
		void overlapsWith_firstOneInsideSecondOne_true();
		void overlapsWith_touching_true();
		void overlapsWith_crossingWithCenterOutside_true();
		void overlapsWith_crossingWithCenterInside_true();
		void overlapsWith_closeTogetherButTooSmallDiameters_false();
	};
}
}

#endif
