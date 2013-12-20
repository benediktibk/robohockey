#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOPOSITIONSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOPOSITIONSTATETEST_H

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
	class DriveToPositionStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(DriveToPositionStateTest);
		CPPUNIT_TEST(nextState_reachedTarget_nextStateIsLeavePuckState);
		CPPUNIT_TEST(nextState_cantReachTarget_nextStateIsLeavePuckState);
		CPPUNIT_TEST(nextState_canReachTarget_nextStateIs0);
		CPPUNIT_TEST(nextState_puckIsNotCollected_nextStateIsDriveToCollectPuck);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_reachedTarget_nextStateIsLeavePuckState();
		void nextState_cantReachTarget_nextStateIsLeavePuckState();
		void nextState_canReachTarget_nextStateIs0();
		void nextState_puckIsNotCollected_nextStateIsDriveToCollectPuck();
	
};
}
}
}
}

#endif


