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
	class DriveToColllectPuckStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(DriveToColllectPuckStateTest);
		CPPUNIT_TEST(nextState_numberOfKnownPucksIs0_nextStateIsFindPuckState);
		CPPUNIT_TEST(nextState_reachedTargetAndPuckIsCollectable_nextStateIsCollectPuckState);
		CPPUNIT_TEST(nextState_canReachTarget_nextStateIsDriveToCollectPuckState);
		CPPUNIT_TEST(nextState_cantReachTarget_nextStateIsInitialState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_numberOfKnownPucksIs0_nextStateIsFindPuckState();
		void nextState_reachedTargetAndPuckIsCollectable_nextStateIsCollectPuckState();
		void nextState_canReachTarget_nextStateIsDriveToCollectPuckState();
		void nextState_cantReachTarget_nextStateIsInitialState();

};
}
}
}
}

#endif
