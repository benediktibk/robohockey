#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_FINDPUCKTURNTOSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_FINDPUCKTURNTOSTATETEST_H

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
	class FindPuckTurnToStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FindPuckTurnToStateTest);
		CPPUNIT_TEST(nextState_foundPuck_nextStateIsVerifyPuckState);
		CPPUNIT_TEST(nextState_emptyTargetListAndTargetReached_nextStateIsFindPuckState);
		CPPUNIT_TEST(nextState_targetList_nextStateIsFindPuckTurnToState);
		CPPUNIT_TEST(nextState_foundPuckAndLimitReachedAndEmptyTargetListAndTargetReached_nextStateIsFindPuckState);
		CPPUNIT_TEST(nextState_emptyTargetListAndTargetNotReached_nextStateIsFindPuckTurnToState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_foundPuck_nextStateIsVerifyPuckState();
		void nextState_emptyTargetListAndTargetReached_nextStateIsFindPuckState();
		void nextState_targetList_nextStateIsFindPuckTurnToState();
		void nextState_foundPuckAndLimitReachedAndEmptyTargetListAndTargetReached_nextStateIsFindPuckState();
		void nextState_emptyTargetListAndTargetNotReached_nextStateIsFindPuckTurnToState();

};
}
}
}
}

#endif


