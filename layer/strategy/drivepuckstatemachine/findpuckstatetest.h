#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_FINDPUCKSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_FINDPUCKSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace DrivePuckStateMachine
{
	class FindPuckStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FindPuckStateTest);
		CPPUNIT_TEST(nextState_targetReached_nextStateIsVerifyPuckState);
		CPPUNIT_TEST(nextState_cantReachTarget_nextStateIsFindPuckState);
		CPPUNIT_TEST(nextState_canReachTarget_nextStateIs0);
		CPPUNIT_TEST(nextState_stuckAtObstacle_nextStateIsLeavePuckState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_targetReached_nextStateIsVerifyPuckState();
		void nextState_cantReachTarget_nextStateIsFindPuckState();
		void nextState_canReachTarget_nextStateIs0();
		void nextState_stuckAtObstacle_nextStateIsLeavePuckState();
	
};
}
}
}
}

#endif


