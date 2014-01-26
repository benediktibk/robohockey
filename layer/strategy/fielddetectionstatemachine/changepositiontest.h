#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHANGEPOSITIONTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHANGEPOSITIONTEST_H

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
class ChangePositionTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ChangePositionTest);
		CPPUNIT_TEST(nextState_didntReachedTarget_NULL);
		CPPUNIT_TEST(nextState_cantReachTarget_detectField);
		CPPUNIT_TEST(nextState_reachedTarget_detectField);
		CPPUNIT_TEST(update_updateSeveralTimes_robotFunctionGetCalledOnlyOnce);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_didntReachedTarget_NULL();
		void nextState_cantReachTarget_detectField();
		void nextState_reachedTarget_detectField();
		void update_updateSeveralTimes_robotFunctionGetCalledOnlyOnce();

	};
}
}
}
}

#endif
