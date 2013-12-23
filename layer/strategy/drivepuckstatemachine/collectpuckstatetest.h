#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_COLLECTPUCKSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_COLLECTPUCKSTATETEST_H

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
	class CollectPuckStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CollectPuckStateTest);
		CPPUNIT_TEST(nextState_puckCollected_nextStateIsDriveToPositionState);
		CPPUNIT_TEST(nextState_cantReachTarget_nextStatedIsDriveToCollectPuckState);
		CPPUNIT_TEST(nextState_canReachTarget_nextStatedIs0);
		CPPUNIT_TEST(nextState_puckIsNotCollectable_nextStateIsDriveToCollectPuckState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_puckCollected_nextStateIsDriveToPositionState();
		void nextState_cantReachTarget_nextStatedIsDriveToCollectPuckState();
		void nextState_canReachTarget_nextStatedIs0();
		void nextState_puckIsNotCollectable_nextStateIsDriveToCollectPuckState();

};
}
}
}
}

#endif
