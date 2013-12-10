#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_ACHIEVEGOALSTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_ACHIEVEGOALSTEST_H

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
class AchieveGoalsTest:
        public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(AchieveGoalsTest);
        CPPUNIT_TEST(nextState_stopMovement_pause);
        CPPUNIT_TEST(nextState_gameOver_pause);
        CPPUNIT_TEST(nextState_achievedGoals3_hideEnemyPucks);
        CPPUNIT_TEST(nextState_achievedGoals1_notHideEnemyPucks);
        CPPUNIT_TEST(nextState_achievedGoals1_notPause);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_stopMovement_pause();
        void nextState_gameOver_pause();
        void nextState_achievedGoals3_hideEnemyPucks();
        void nextState_achievedGoals1_notHideEnemyPucks();
        void nextState_achievedGoals1_notPause();




    
    };
}
}
}
}

#endif

