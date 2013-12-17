#include "common/watchtest.h"
#include "common/watchimpl.h"
#include <unistd.h>

using namespace RoboHockey::Common;

void WatchTest::getTimeAndRestart_twiceDirectBehindCalled_0()
{
	WatchImpl watch;

	watch.getTimeAndRestart();
	double time = watch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, time, 0.01);
}

void WatchTest::getTimeAndRestart_sleepOf200ms_02()
{
	WatchImpl watch;

	watch.getTimeAndRestart();
	usleep(200000);
	double time = watch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, time, 0.01);
}

void WatchTest::getTime_twiceCalled_notRestarted()
{
	WatchImpl watch;

	watch.getTimeAndRestart();
	usleep(100000);
	watch.getTime();
	double time = watch.getTime();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1, time, 0.01);
}
