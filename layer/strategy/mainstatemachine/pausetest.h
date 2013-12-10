#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_PAUSETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_PAUSETEST_H

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
    class PauseTest :
            public CPPUNIT_NS::TestFixture
	{
        CPPUNIT_TEST_SUITE(PauseTest);
        CPPUNIT_TEST(nextState_detectionStart_Calibrate);
        CPPUNIT_TEST(nextState_gameStart_AchieveGoals);
        CPPUNIT_TEST(nextState_achieveGoals2_AchieveGoals);
        CPPUNIT_TEST(nextState_gameOver_Pause);
        CPPUNIT_TEST(nextState_stopMovement_Pause);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_detectionStart_Calibrate();
        void nextState_gameStart_AchieveGoals();
        void nextState_achieveGoals2_AchieveGoals();
        void nextState_gameOver_Pause();
        void nextState_stopMovement_Pause();
	};
}
}
}
}

#endif
