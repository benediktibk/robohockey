#ifndef ROBOHOCKEY_LAYER_STRATEGY_CALIBRATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_CALIBRATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
class CalibrateTest:
        public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(CalibrateTest);
        CPPUNIT_TEST(nextState_gameStart_achieveGoals);
        CPPUNIT_TEST(nextState_stopMovement_pause);
        CPPUNIT_TEST(nextState_gameOver_pause);
        CPPUNIT_TEST(nextState_detectionStart_notAchieveGoals);
        CPPUNIT_TEST(nextState_gameStartAndStopMovement_notInitialState);
        CPPUNIT_TEST(nextState_gameOverAndStopMovement_pause);
        CPPUNIT_TEST(nextState_gameStartAndGameOver_notInitialState);
        CPPUNIT_TEST(nextState_detectionStart_notPause);
        CPPUNIT_TEST(nextState_detectionStartAndGameStart_AchieveGoals);
        CPPUNIT_TEST(nextState_GameStartAndGameOver_notCalibrate);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_gameStart_achieveGoals();
        void nextState_stopMovement_pause();
        void nextState_gameOver_pause();
        void nextState_detectionStart_notAchieveGoals();
        void nextState_gameStartAndStopMovement_notInitialState();
        void nextState_gameOverAndStopMovement_pause();
        void nextState_gameStartAndGameOver_notInitialState();
        void nextState_detectionStart_notPause();
        void nextState_detectionStartAndGameStart_AchieveGoals();
        void nextState_GameStartAndGameOver_notCalibrate();
};

}
}
}

#endif
