#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMACHINETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMACHINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class StateMachineTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(StateMachineTest);
		CPPUNIT_TEST(update_empty_stateGotAtLeastOneCallToNextState);
		CPPUNIT_TEST(update_noStateChange_stateGotAtLeastOneCallToUpdate);
		CPPUNIT_TEST(update_empty_robotGotNoCallsToUpdateSensorData);
		CPPUNIT_TEST(update_empty_robotGotNoCallsToUpdateActuators);
		CPPUNIT_TEST(update_stateChange_currentStateIsNewOne);
		CPPUNIT_TEST(update_stateChange_currentStateGotAtLeastOneCallToUpdate);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_empty_stateGotAtLeastOneCallToNextState();
		void update_noStateChange_stateGotAtLeastOneCallToUpdate();
		void update_empty_robotGotNoCallsToUpdateSensorData();
		void update_empty_robotGotNoCallsToUpdateActuators();
		void update_stateChange_currentStateIsNewOne();
		void update_stateChange_currentStateGotAtLeastOneCallToUpdate();
	};
}
}
}
}

#endif
