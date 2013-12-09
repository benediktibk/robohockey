#ifndef ROBOHOCKEY_LAYER_STRATEGY_ACHIEVEGOALSTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_ACHIEVEGOALSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
class AchieveGoalsTest:
        public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(AchieveGoalsTest);
        CPPUNIT_TEST(nextState_stopMovement_pause);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_stopMovement_pause();




    
    };
}
}
}

#endif


#ifndef ROBOHOCKEY_LAYER_STRATEGY_INITIALSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_INITIALSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class InitialStateTest :
            public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(InitialStateTest);
        CPPUNIT_TEST(nextState_detectionStart_calibrate);
        CPPUNIT_TEST(nextState_gameStartAndDetectionStart_calibrate);
        CPPUNIT_TEST_SUITE_END();

    private:
        void nextState_detectionStart_calibrate();
        void nextState_gameStartAndDetectionStart_calibrate();
    };
}
}
}

#endif
