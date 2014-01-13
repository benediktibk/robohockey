#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_VERIFYPUCKSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_VERIFYPUCKSTATETEST_H

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
	class VerifyPuckStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(VerifyPuckStateTest);
		CPPUNIT_TEST(nextState_correctPuckIsCollectable_nextStateIsCollectPuckState);
		CPPUNIT_TEST(nextState_wrongPuckIsCollectable_nextStateIsDriveToCollectPuckState);
		CPPUNIT_TEST(nextState_correctPuckIsNotCollectable_nextStateIsDriveToCollectPuckState);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_correctPuckIsCollectable_nextStateIsCollectPuckState();
		void nextState_wrongPuckIsCollectable_nextStateIsDriveToCollectPuckState();
		void nextState_correctPuckIsNotCollectable_nextStateIsDriveToCollectPuckState();

};
}
}
}
}

#endif


