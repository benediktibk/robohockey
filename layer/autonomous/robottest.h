#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RobotTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotTest);
		CPPUNIT_TEST(goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraight);
		CPPUNIT_TEST(stuckAtObstacle_obstacleDirectInFront_true);
		CPPUNIT_TEST(stuckAtObstacle_noObstacleDirectInFront_false);
		CPPUNIT_TEST(reachedTarget_currentPositionDifferentToTarget_false);
		CPPUNIT_TEST(reachedTarget_currentPositionIsTargetPosition_true);
		CPPUNIT_TEST(updateActuators_empty_layerBelowGotAtLeastOneCallToUpdateActuators);
		CPPUNIT_TEST(updateSensorData_empty_layerBelowGotAtLeastOneCallToUpdateSensorData);
		CPPUNIT_TEST(stop_empty_engineGotAtLeastOneCallToStop);
		CPPUNIT_TEST_SUITE_END();

	private:
		void goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraight();
		void stuckAtObstacle_obstacleDirectInFront_true();
		void stuckAtObstacle_noObstacleDirectInFront_false();
		void reachedTarget_currentPositionDifferentToTarget_false();
		void reachedTarget_currentPositionIsTargetPosition_true();
		void updateActuators_empty_layerBelowGotAtLeastOneCallToUpdateActuators();
		void updateSensorData_empty_layerBelowGotAtLeastOneCallToUpdateSensorData();
		void stop_empty_engineGotAtLeastOneCallToStop();
	};
}
}
}

#endif
