#include "common/watchtest.h"
#include "common/watch.h"
#include <math.h>

using namespace RoboHockey::Common;

void WatchTest::restart_timeNot0_timeIs0()
{
    Watch watch;
    double x = 0;

    watch.restart();
    for(int i = 0; i < 100; i++)
    {
        x += sqrt(i);
    }

    watch.restart();

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, watch.getTime(), 0.0001);
}
