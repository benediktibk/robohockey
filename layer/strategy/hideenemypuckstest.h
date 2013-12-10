#ifndef ROBOHOCKEY_LAYER_STRATEGY_HIDEENEMYPUCKSTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_HIDEENEMYPUCKSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
class HideEnemyPucksTest:
        public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(HideEnemyPucksTest);
        CPPUNIT_TEST(nextState_notAllEnemyPucksHidden_notAchieveGoals);
        CPPUNIT_TEST(nextState_allEnemyPucksHidden_DriveToFinalPosition);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_notAllEnemyPucksHidden_notAchieveGoals();
        void nextState_allEnemyPucksHidden_DriveToFinalPosition();
    };
}
}
}

#endif
