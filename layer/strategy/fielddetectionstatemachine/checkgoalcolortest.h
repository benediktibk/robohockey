#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHECKGOALCOLORTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHECKGOALCOLORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
class CheckGoalColorTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CheckGoalColorTest);
		CPPUNIT_TEST(nextState_successfulColorCheckNoResponse_NULL);
		CPPUNIT_TEST(nextState_unsuccessfulColorCheck_NULL);
		CPPUNIT_TEST(nextState_successfulColorCheckGotResponse_calibrationFinished);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_successfulColorCheckNoResponse_NULL();
		void nextState_unsuccessfulColorCheck_NULL();
		void nextState_successfulColorCheckGotResponse_calibrationFinished();
	};
}
}
}
}

#endif


