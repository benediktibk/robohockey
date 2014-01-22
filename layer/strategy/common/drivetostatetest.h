#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETOSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETOSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
class DriveToStateTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(DriveToStateTest);
		CPPUNIT_TEST(nextState_didntReachedTarget_NULL);
		CPPUNIT_TEST(nextState_reachedTarget_stateAfterReachedTarget);
		CPPUNIT_TEST(nextState_cantReachTarget_stateAfterCantReachTarget);
		CPPUNIT_TEST(nextState_stuckAtObstacle_stateAfterStuckAtObstacle);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_didntReachedTarget_NULL();
		void nextState_reachedTarget_stateAfterReachedTarget();
		void nextState_cantReachTarget_stateAfterCantReachTarget();
		void nextState_stuckAtObstacle_stateAfterStuckAtObstacle();
		
	};
}
}
}
}

#endif


