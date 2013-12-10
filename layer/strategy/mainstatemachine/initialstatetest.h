#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_INITIALSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_INITIALSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace MainStateMachine
{
	class InitialStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(InitialStateTest);
        CPPUNIT_TEST(nextState_detectionStart_calibrate);
        CPPUNIT_TEST(nextState_gameStartAndNotDetectionStart_notCalibrate);
		CPPUNIT_TEST_SUITE_END();

	private:
        void nextState_detectionStart_calibrate();
        void nextState_gameStartAndNotDetectionStart_notCalibrate();
	};
}
}
}
}

#endif
