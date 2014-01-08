#include "common/watchtest.h"
#include "common/watchimpl.h"
#include <unistd.h>

using namespace RoboHockey::Common;

void WatchTest::getTime_twiceCalled_notRestarted()
{
	WatchImpl watch;

	watch.getTimeAndRestart();
	usleep(100000);
	watch.getTime();
	double time = watch.getTime();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1, time, 0.01);
}
