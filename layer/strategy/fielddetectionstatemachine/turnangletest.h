#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLETEST_H

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
	class TurnAngleTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(TurnAngleTest);
		CPPUNIT_TEST(nextState_targetReached_detectField);
		CPPUNIT_TEST(nextState_targetNotReached_NULL);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_targetReached_detectField();
		void nextState_targetNotReached_NULL();
		
	};
}
}
}
}

#endif

