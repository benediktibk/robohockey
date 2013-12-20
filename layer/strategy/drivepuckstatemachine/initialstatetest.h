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
		CPPUNIT_TEST(nextState_puckCollected_nextStateIsLeavePuck);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_puckCollected_nextStateIsLeavePuck();

	};
}
}
}
}

#endif
