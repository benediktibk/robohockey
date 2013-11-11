#ifndef ROBOHOCKEY_COMMON_WATCHTEST_H
#define ROBOHOCKEY_COMMON_WATCHTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
    class WatchTest :
            public CPPUNIT_NS::TestFixture
    {
        CPPUNIT_TEST_SUITE(WatchTest);
        CPPUNIT_TEST(restart_timeNot0_timeIs0);
        CPPUNIT_TEST_SUITE_END();

    private:
        void restart_timeNot0_timeIs0();
    };
}
}
#endif // WATCHTEST_H
