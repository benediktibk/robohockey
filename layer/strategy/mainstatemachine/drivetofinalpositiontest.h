#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_DRIVETOFINALPOSITIONTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_DRIVETOFINALPOSITIONTEST_H

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
class DriveToFinalPositionTest :
        public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(DriveToFinalPositionTest);
        CPPUNIT_TEST(nextState_stopMovement_Pause);
        CPPUNIT_TEST(nextState_achieveGoals2_AchieveGoals);
        CPPUNIT_TEST(nextState_gameOver_Pause);
        CPPUNIT_TEST(nextState_notAllEnemyPucksHidden_HideEnemyPucks);
		CPPUNIT_TEST(nextState_notAllEnemyPucksHidden_DriveToFinalPosition);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_stopMovement_Pause();
        void nextState_gameOver_Pause();
        void nextState_achieveGoals2_AchieveGoals();
        void nextState_notAllEnemyPucksHidden_HideEnemyPucks();
		void nextState_notAllEnemyPucksHidden_DriveToFinalPosition();
    };
}
}
}
}

#endif
