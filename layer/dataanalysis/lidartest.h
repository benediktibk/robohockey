#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "common/angle.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class LidarMock;
}

namespace DataAnalysis
{
	class LidarTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LidarTest);
		CPPUNIT_TEST(constructor_empty_maximumAngleLeftIs0);
		CPPUNIT_TEST(constructor_empty_maximumAngleRightIs0);
		CPPUNIT_TEST(getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance);
		CPPUNIT_TEST(getAllObjects_oneTooBigObjectInFront_objectCountIs0);
		CPPUNIT_TEST(getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_twoObjects_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIsAtLeast1);
		CPPUNIT_TEST(getAllObjects_oneObjectBehindAnotherOneRight_objectCountIsAtLeast1);
		CPPUNIT_TEST(getAllObjects_objectAtLeftBorder_objectCountIs0);
		CPPUNIT_TEST(getAllObjects_objectAtRightBorder_objectCountIs0);
		CPPUNIT_TEST(getAllObjects_realWorldExample_runsThroughWithoutACrash);
		CPPUNIT_TEST(getAllObjects_puckDirectInFront_onlyObjectIsCorrect);
		CPPUNIT_TEST(getAllobjects_oneBoundaryPostInRange_diameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckALittleBitDistant_diameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuck_positionAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckInQuiteADistanceVersion1_distanceAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckInQuiteADistanceVersion2_distanceAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_maximumDistanceToBoundaryPostOfOwnFieldPart_distanceAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_twoObjectsInFrontOfWall_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_twoObjectsWithADistanceOfOneMeter_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_twoBorderStonesInFrontOfWall_objectCountIs2);
		CPPUNIT_TEST(isObstacleInFront_noObstacleInFront_false);
		CPPUNIT_TEST(isObstacleInFront_puckCollected_false);
		CPPUNIT_TEST(isObstacleInFront_obstacleOnLeftSide_true);
		CPPUNIT_TEST(isObstacleInFront_obstacleOnRightSide_true);
		CPPUNIT_TEST(isObstacleInFront_severalBoundPostsAndOtherRobotFarAway_false);
		CPPUNIT_TEST(isObstacleInFront_robotVeryCloseAtTheSide_true);
		CPPUNIT_TEST(isObstacleInFront_robotVeryCloseAheadAtTheSide_true);
		CPPUNIT_TEST(isObstacleInFront_robotFarDistance_false);
		CPPUNIT_TEST(isPuckCollected_noPuckInCloseDistance_false);
		CPPUNIT_TEST(isPuckCollected_closeEnough_true);
		CPPUNIT_TEST(isPuckCollected_directInTheMiddle_true);
		CPPUNIT_TEST(isPuckCollected_atLeftEndOfClutch_true);
		CPPUNIT_TEST(isPuckCollected_atRightEndOfClutch_true);
		CPPUNIT_TEST(isPuckCollected_rightOfClutch_false);
		CPPUNIT_TEST(isPuckCollected_leftOfClutch_false);
		CPPUNIT_TEST(isPuckCollected_asDistantAsAfterOneQuarterTurn_true);
		CPPUNIT_TEST(isPuckCollected_slightlyMoreDistantThanOneQuarterTurn_false);
		CPPUNIT_TEST(isPuckCollectable_noPuckInCloseDistance_false);
		CPPUNIT_TEST(isPuckCollectable_puckCollected_true);
		CPPUNIT_TEST(isPuckCollectable_puckStraightAheadCloseEnough_true);
		CPPUNIT_TEST(isPuckCollectable_puckStraightAheadButTooDistant_false);
		CPPUNIT_TEST(isPuckCollectable_puckCloseAndALittleBitLeft_true);
		CPPUNIT_TEST(isPuckCollectable_puckCloseAndALittleBitRight_true);
		CPPUNIT_TEST(isPuckCollectable_puckCloseButTooMuchLeft_false);
		CPPUNIT_TEST(isPuckCollectable_puckCloseButTooMuchRight_false);
		CPPUNIT_TEST(isPuckCollectable_twoPucksBeside_true);
		CPPUNIT_TEST(isPuckCollectable_onePuckCloseEnoughtAndAnotherOneStraightAhead_false);
		CPPUNIT_TEST(getMaximumAngleLeft_noObjects_piHalf);
		CPPUNIT_TEST(getMaximumAngleRight_noObjects_minusPiHalf);
		CPPUNIT_TEST(getMaximumAngleLeft_objectAtLeftBorder_reducedViewArea);
		CPPUNIT_TEST(getMaximumAngleRight_objectAtRightBorder_reducedViewArea);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_maximumAngleLeftIs0();
		void constructor_empty_maximumAngleRightIs0();
		void getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance();
		void getAllObjects_oneTooBigObjectInFront_objectCountIs0();
		void getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect();
		void getAllObjects_twoObjects_objectCountIs2();
		void getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIsAtLeast1();
		void getAllObjects_oneObjectBehindAnotherOneRight_objectCountIsAtLeast1();
		void getAllObjects_objectAtLeftBorder_objectCountIs0();
		void getAllObjects_objectAtRightBorder_objectCountIs0();
		void getAllObjects_realWorldExample_runsThroughWithoutACrash();
		void getAllObjects_puckDirectInFront_onlyObjectIsCorrect();
		void getAllobjects_oneBoundaryPostInRange_diameterIsCorrect();
		void getAllObjects_onePuckALittleBitDistant_diameterIsCorrect();
		void getAllObjects_onePuck_positionAndDiameterIsCorrect();
		void getAllObjects_onePuckInQuiteADistanceVersion1_distanceAndDiameterIsCorrect();
		void getAllObjects_onePuckInQuiteADistanceVersion2_distanceAndDiameterIsCorrect();
		void getAllObjects_maximumDistanceToBoundaryPostOfOwnFieldPart_distanceAndDiameterIsCorrect();
		void getAllObjects_twoObjectsInFrontOfWall_objectCountIs2();
		void getAllObjects_twoObjectsWithADistanceOfOneMeter_objectCountIs2();
		void getAllObjects_twoBorderStonesInFrontOfWall_objectCountIs2();
		void isObstacleInFront_noObstacleInFront_false();
		void isObstacleInFront_puckCollected_false();
		void isObstacleInFront_obstacleOnLeftSide_true();
		void isObstacleInFront_obstacleOnRightSide_true();
		void isObstacleInFront_severalBoundPostsAndOtherRobotFarAway_false();
		void isObstacleInFront_robotVeryCloseAtTheSide_true();
		void isObstacleInFront_robotVeryCloseAheadAtTheSide_true();
		void isObstacleInFront_robotFarDistance_false();
		void isPuckCollected_noPuckInCloseDistance_false();
		void isPuckCollected_closeEnough_true();
		void isPuckCollected_directInTheMiddle_true();
		void isPuckCollected_atLeftEndOfClutch_true();
		void isPuckCollected_atRightEndOfClutch_true();
		void isPuckCollected_rightOfClutch_false();
		void isPuckCollected_leftOfClutch_false();
		void isPuckCollected_asDistantAsAfterOneQuarterTurn_true();
		void isPuckCollected_slightlyMoreDistantThanOneQuarterTurn_false();
		void isPuckCollectable_noPuckInCloseDistance_false();
		void isPuckCollectable_puckCollected_true();
		void isPuckCollectable_puckStraightAheadCloseEnough_true();
		void isPuckCollectable_puckStraightAheadButTooDistant_false();
		void isPuckCollectable_puckCloseAndALittleBitLeft_true();
		void isPuckCollectable_puckCloseAndALittleBitRight_true();
		void isPuckCollectable_puckCloseButTooMuchLeft_false();
		void isPuckCollectable_puckCloseButTooMuchRight_false();
		void isPuckCollectable_twoPucksBeside_true();
		void isPuckCollectable_onePuckCloseEnoughtAndAnotherOneStraightAhead_false();
		void getMaximumAngleLeft_noObjects_piHalf();
		void getMaximumAngleRight_noObjects_minusPiHalf();
		void getMaximumAngleLeft_objectAtLeftBorder_reducedViewArea();
		void getMaximumAngleRight_objectAtRightBorder_reducedViewArea();

	private:
		static const double m_maximumDistance;
		static const Common::Angle m_maximumAngle;
	};
}
}
}

#endif
