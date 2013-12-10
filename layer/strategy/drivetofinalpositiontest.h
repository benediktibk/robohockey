#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVETOFINALPOSITIONTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVETOFINALPOSITIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
class DriveToFinalPositionTest :
        public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(DriveToFinalPositionTest);
        CPPUNIT_TEST(nextState_stopMovement_pause);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_stopMovement_pause();
    };
}
}
}

#endif
