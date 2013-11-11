#ifndef ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVERTEST_H
#define ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class RobotDriverTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotDriverTest);
		CPPUNIT_TEST(update_targetReached_targetInModelReached);
		CPPUNIT_TEST(update_stuckAtObstacle_stuckAtObstacleInModel);
		CPPUNIT_TEST(update_twoFieldObjects_twoFieldObjectsInModel);
		CPPUNIT_TEST(update_stuckAtObstacle_targetPositionsIsEmpty);
		CPPUNIT_TEST(update_newTargetPositionsAndTargetReached_targetOfRobotIsFirstPosition);
		CPPUNIT_TEST(update_newTargetPositionsAndTargetReached_firstTargetPositionIsMissingInModel);
		CPPUNIT_TEST(update_newTargetPositionsAndTargetNotReached_targetOfRobotIsUnchanged);
		CPPUNIT_TEST(update_empty_robotGotAtLeastOneCallToUpdateSensorData);
		CPPUNIT_TEST(update_empty_robotGotAtLeastOneCallToUpdateActuators);
		CPPUNIT_TEST(update_stuckAtObstacle_robotGotAtLeastOneCallToStop);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_targetReached_targetInModelReached();
		void update_stuckAtObstacle_stuckAtObstacleInModel();
		void update_twoFieldObjects_twoFieldObjectsInModel();
		void update_stuckAtObstacle_targetPositionsIsEmpty();
		void update_newTargetPositionsAndTargetReached_targetOfRobotIsFirstPosition();
		void update_newTargetPositionsAndTargetReached_firstTargetPositionIsMissingInModel();
		void update_newTargetPositionsAndTargetNotReached_targetOfRobotIsUnchanged();
		void update_empty_robotGotAtLeastOneCallToUpdateSensorData();
		void update_empty_robotGotAtLeastOneCallToUpdateActuators();
		void update_stuckAtObstacle_robotGotAtLeastOneCallToStop();
	};
}
}
}

#endif
