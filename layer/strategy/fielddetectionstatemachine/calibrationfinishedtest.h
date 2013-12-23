#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CALIBRATIONFINISHEDTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CALIBRATIONFINISHEDTEST_H

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
	class CalibrationFinishedTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CalibrationFinishedTest);
		CPPUNIT_TEST(nextState_3TargetsReached_NULL);
		CPPUNIT_TEST(nextState_0TargetsReached_DriveTo);
		CPPUNIT_TEST(nextState_1TargetsReached_DriveTo);
		CPPUNIT_TEST_SUITE_END();
	private:
		void nextState_3TargetsReached_NULL();
		void nextState_0TargetsReached_DriveTo();
		void nextState_1TargetsReached_DriveTo();
	};
}
}
}
}

#endif


