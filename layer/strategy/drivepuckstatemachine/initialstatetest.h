#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_INITIALSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_INITIALSTATETEST_H

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
	class InitialStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(InitialStateTest);
		CPPUNIT_TEST(nextState_puckCollected_nextStateIsLeavePuckState);
		CPPUNIT_TEST(nextState_numberOfKnownPucksIs0_nextStateIsFindPuckTurnToState);
		CPPUNIT_TEST(nextState_numberOfKnownPucksIs2_nextStateIsDriveToCollectPuckState);
		CPPUNIT_TEST(nextState_numberOfKnownPucksIs2AndCantReachTargetLimitIsReached_nextStateIsFindPuckTurnToPuckState);
		CPPUNIT_TEST(nextState_stuckAtObstacle_nextStateIsLeavePuckState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_puckCollected_nextStateIsLeavePuckState();
		void nextState_numberOfKnownPucksIs0_nextStateIsFindPuckTurnToState();
		void nextState_numberOfKnownPucksIs2_nextStateIsDriveToCollectPuckState();
		void nextState_numberOfKnownPucksIs2AndCantReachTargetLimitIsReached_nextStateIsFindPuckTurnToPuckState();
		void nextState_stuckAtObstacle_nextStateIsLeavePuckState();

	};
}
}
}
}

#endif
