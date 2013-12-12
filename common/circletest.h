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
		CPPUNIT_TEST(getIntersectionPoints_farAway_resultSizeIs0);
		CPPUNIT_TEST(getIntersectionPoints_touching_resultSizeIs1);
		CPPUNIT_TEST(getIntersectionPoints_intersecting_resultSizeIs2);
		CPPUNIT_TEST(getIntersectionPoints_touching_pointIsCorrect);
		CPPUNIT_TEST(getIntersectionPoints_intersection_pointsCorrect);
		CPPUNIT_TEST(isOnCircle_insideTheCircle_false);
		CPPUNIT_TEST(isOnCircle_outsideTheCircle_false);
		CPPUNIT_TEST(isOnCircle_onTheCircle_true);
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
		void getIntersectionPoints_farAway_resultSizeIs0();
		void getIntersectionPoints_touching_resultSizeIs1();
		void getIntersectionPoints_intersecting_resultSizeIs2();
		void getIntersectionPoints_touching_pointIsCorrect();
		void getIntersectionPoints_intersection_pointsCorrect();
		void isOnCircle_insideTheCircle_false();
		void isOnCircle_outsideTheCircle_false();
		void isOnCircle_onTheCircle_true();
	};
}
}

#endif
