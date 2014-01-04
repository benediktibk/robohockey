#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_LEAVEPUCKSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_LEAVEPUCKSTATETEST_H

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
	class LeavePuckStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LeavePuckStateTest);
		CPPUNIT_TEST(nextState_cantReachTarget_nextStateIsInitialState);
		CPPUNIT_TEST(nextState_reachedTargetAndNumberOfKnownPucksIs0_nextStateIsFindPuckState);
		CPPUNIT_TEST(nextState_reachedTargetAndNumberOfKnownPucksIsNot0_nextStateIsDriveToCollectPuckState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_cantReachTarget_nextStateIsInitialState();
		void nextState_reachedTargetAndNumberOfKnownPucksIs0_nextStateIsFindPuckState();
		void nextState_reachedTargetAndNumberOfKnownPucksIsNot0_nextStateIsDriveToCollectPuckState();
	
};
}
}
}
}

#endif


