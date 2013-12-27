#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKSTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKSTEST_H

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
class HideEnemyPucksTest:
        public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(HideEnemyPucksTest);
        CPPUNIT_TEST(nextState_notAllEnemyPucksHidden_notAchieveGoals);
        CPPUNIT_TEST(nextState_allEnemyPucksHidden_DriveToFinalPosition);
        CPPUNIT_TEST(nextState_stopMovement_Pause);
        CPPUNIT_TEST(nextState_gameOver_Pause);
        CPPUNIT_TEST(nextState_achievedGoals2_AchieveGoals);
		CPPUNIT_TEST(nextState_nextState_hideEnemyPucks);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_notAllEnemyPucksHidden_notAchieveGoals();
        void nextState_stopMovement_Pause();
        void nextState_gameOver_Pause();
        void nextState_allEnemyPucksHidden_DriveToFinalPosition();
        void nextState_achievedGoals2_AchieveGoals();
		void nextState_nextState_hideEnemyPucks();
    };
}
}
}
}

#endif
