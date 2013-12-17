#include "common/watchtest.h"
#include "common/watch.h"
#include <unistd.h>

using namespace RoboHockey::Common;

void WatchTest::getTimeAndRestart_twiceDirectBehindCalled_0()
{
	Watch watch;

	watch.getTimeAndRestart();
	double time = watch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, time, 0.01);
}

void WatchTest::getTimeAndRestart_sleepOf200ms_02()
{
	Watch watch;

	watch.getTimeAndRestart();
	usleep(200000);
	double time = watch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, time, 0.01);
}
