#include "common/timesmoothedbooleantest.h"
#include "common/timesmoothedboolean.h"
#include "common/watchmock.h"

using namespace RoboHockey::Common;

void TimeSmoothedBooleanTest::constructor_initialValueTrue_valueIsTrue()
{
	WatchMock watch;
	TimeSmoothedBoolean boolean(watch, true, 1);

	CPPUNIT_ASSERT(boolean.get());
}

void TimeSmoothedBooleanTest::constructor_initialValueFalse_valueIsFalse()
{
	WatchMock watch;
	TimeSmoothedBoolean boolean(watch, false, 1);

	CPPUNIT_ASSERT(!boolean.get());
}

void TimeSmoothedBooleanTest::update_trueAndThenFalseNearlyLongEnough_true()
{
	WatchMock watch;
	TimeSmoothedBoolean boolean(watch, true, 1);

	boolean.update(false);
	watch.setTime(0.1);
	boolean.update(false);
	watch.setTime(1);
	boolean.update(true);
	watch.setTime(1.9999);
	boolean.update(false);

	CPPUNIT_ASSERT(boolean.get());
}

void TimeSmoothedBooleanTest::update_falseAndThenTrueNearlyLongEnough_false()
{
	WatchMock watch;
	TimeSmoothedBoolean boolean(watch, false, 1);

	boolean.update(true);
	watch.setTime(0.1);
	boolean.update(true);
	watch.setTime(1);
	boolean.update(false);
	watch.setTime(1.9999);
	boolean.update(true);

	CPPUNIT_ASSERT(!boolean.get());
}

void TimeSmoothedBooleanTest::update_trueAndThenFalseLongEnough_false()
{
	WatchMock watch;
	TimeSmoothedBoolean boolean(watch, true, 1);

	watch.setTime(1.00001);
	boolean.update(false);

	CPPUNIT_ASSERT(!boolean.get());
}

void TimeSmoothedBooleanTest::update_falseAndThenTrueLongEnough_true()
{
	WatchMock watch;
	TimeSmoothedBoolean boolean(watch, false, 1);

	watch.setTime(1.00001);
	boolean.update(true);

	CPPUNIT_ASSERT(boolean.get());
}
