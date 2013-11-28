#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

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
		CPPUNIT_TEST(getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance);
		CPPUNIT_TEST(getAllObjects_oneTooBigObjectInFront_objectCountIs0);
		CPPUNIT_TEST(getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_twoObjects_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_oneObjectBehindAnotherOneRight_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_objectAtLeftBorder_objectCountIs1);
		CPPUNIT_TEST(getAllObjects_objectAtRightBorder_objectCountIs1);
		CPPUNIT_TEST(getAllObjects_realWorldExample_runsThroughWithoutACrash);
		CPPUNIT_TEST(getAllObjects_objectRightOfView_positionOfOnlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_objectLeftOfView_positionOfOnlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_puckDirectInFront_onlyObjectIsCorrect);
		CPPUNIT_TEST(getAllobjects_oneBoundaryPostInRange_diameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckALittleBitDistant_diameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuck_positionAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckInQuiteADistanceVersion1_distanceAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckInQuiteADistanceVersion2_distanceAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_maximumDistanceToBoundaryPostOfOwnFieldPart_distanceAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_twoObjectsInFrontOfWall_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_twoObjectsWithADistanceOfOneMeter_objectCountIs2);
		CPPUNIT_TEST(isObstacleInFront_noObstacleInFront_false);
		CPPUNIT_TEST(isObstacleInFront_puckCollected_false);
		CPPUNIT_TEST(isObstacleInFront_obstacleOnLeftSide_true);
		CPPUNIT_TEST(isObstacleInFront_obstacleOnRightSide_true);
		CPPUNIT_TEST(isObstacleInFront_severalBoundPostsAndOtherRobotFarAway_false);
		CPPUNIT_TEST(isObstacleInFront_robotVeryCloseAtTheSide_true);
		CPPUNIT_TEST(isObstacleInFront_robotVeryCloseAheadAtTheSide_true);
		CPPUNIT_TEST(isObstacleInFront_robotFarDistance_false);
		CPPUNIT_TEST(isPuckCollected_noPuckInCloseDistance_false);
		CPPUNIT_TEST(isPuckCollected_onPuckNearlyCloseEnough_false);
		CPPUNIT_TEST(isPuckCollected_directInTheMiddle_true);
		CPPUNIT_TEST(isPuckCollected_atLeftEndOfClutch_true);
		CPPUNIT_TEST(isPuckCollected_atRightEndOfClutch_true);
		CPPUNIT_TEST(isPuckCollected_rightOfClutch_false);
		CPPUNIT_TEST(isPuckCollected_leftOfClutch_false);
		CPPUNIT_TEST(isPuckCollected_asDistantAsAfterOneQuarterTurn_true);
		CPPUNIT_TEST(isPuckCollected_slightlyMoreDistantThanOneQuarterTurn_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance();
		void getAllObjects_oneTooBigObjectInFront_objectCountIs0();
		void getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect();
		void getAllObjects_twoObjects_objectCountIs2();
		void getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIs2();
		void getAllObjects_oneObjectBehindAnotherOneRight_objectCountIs2();
		void getAllObjects_objectAtLeftBorder_objectCountIs1();
		void getAllObjects_objectAtRightBorder_objectCountIs1();
		void getAllObjects_realWorldExample_runsThroughWithoutACrash();
		void getAllObjects_objectRightOfView_positionOfOnlyObjectIsCorrect();
		void getAllObjects_objectLeftOfView_positionOfOnlyObjectIsCorrect();
		void getAllObjects_puckDirectInFront_onlyObjectIsCorrect();
		void getAllobjects_oneBoundaryPostInRange_diameterIsCorrect();
		void getAllObjects_onePuckALittleBitDistant_diameterIsCorrect();
		void getAllObjects_onePuck_positionAndDiameterIsCorrect();
		void getAllObjects_onePuckInQuiteADistanceVersion1_distanceAndDiameterIsCorrect();
		void getAllObjects_onePuckInQuiteADistanceVersion2_distanceAndDiameterIsCorrect();
		void getAllObjects_maximumDistanceToBoundaryPostOfOwnFieldPart_distanceAndDiameterIsCorrect();
		void getAllObjects_twoObjectsInFrontOfWall_objectCountIs2();
		void getAllObjects_twoObjectsWithADistanceOfOneMeter_objectCountIs2();
		void isObstacleInFront_noObstacleInFront_false();
		void isObstacleInFront_puckCollected_false();
		void isObstacleInFront_obstacleOnLeftSide_true();
		void isObstacleInFront_obstacleOnRightSide_true();
		void isObstacleInFront_severalBoundPostsAndOtherRobotFarAway_false();
		void isObstacleInFront_robotVeryCloseAtTheSide_true();
		void isObstacleInFront_robotVeryCloseAheadAtTheSide_true();
		void isObstacleInFront_robotFarDistance_false();
		void isPuckCollected_noPuckInCloseDistance_false();
		void isPuckCollected_onPuckNearlyCloseEnough_false();
		void isPuckCollected_directInTheMiddle_true();
		void isPuckCollected_atLeftEndOfClutch_true();
		void isPuckCollected_atRightEndOfClutch_true();
		void isPuckCollected_rightOfClutch_false();
		void isPuckCollected_leftOfClutch_false();
		void isPuckCollected_asDistantAsAfterOneQuarterTurn_true();
		void isPuckCollected_slightlyMoreDistantThanOneQuarterTurn_false();
	};
}
}
}

#endif
