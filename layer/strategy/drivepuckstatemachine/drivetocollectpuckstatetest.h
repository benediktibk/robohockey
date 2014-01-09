#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOCOLLECTPUCKSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOCOLLECTPUCKSTATETEST_H

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
	class DriveToCollectPuckStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(DriveToCollectPuckStateTest);
		CPPUNIT_TEST(nextState_numberOfKnownPucksIs0_nextStateIsFindPuckState);
		CPPUNIT_TEST(nextState_reachedTarget_nextStateIsCollectPuckState);
		CPPUNIT_TEST(nextState_canReachTarget_nextStateIs0);
		CPPUNIT_TEST(nextState_cantReachTarget_nextStateIsInitialState);
		CPPUNIT_TEST(nextState_cantReachTarget_nextStateIsDriveToState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_numberOfKnownPucksIs0_nextStateIsFindPuckState();
		void nextState_reachedTarget_nextStateIsCollectPuckState();
		void nextState_canReachTarget_nextStateIs0();
		void nextState_cantReachTarget_nextStateIsInitialState();
		void nextState_cantReachTarget_nextStateIsDriveToState();

};
}
}
}
}

#endif
