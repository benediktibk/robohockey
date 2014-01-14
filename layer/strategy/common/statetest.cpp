#include "layer/strategy/common/statetest.h"
#include "layer/strategy/common/statemock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/strategy/common/refereemock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

void StateTest::update_updateAlwaysAndCalledThreeTimes_updateInternalWasCalledThreeTimes()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	StateMock state(robot, field, referee, logger, false);

	state.update();
	state.update();
	state.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, state.getCallsToUpdate());
}

void StateTest::update_updateOnlyOnceAndCalledFourTimes_updateInternalWasCalledOnce()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	StateMock state(robot, field, referee, logger, true);

	state.update();
	state.update();
	state.update();
	state.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, state.getCallsToUpdate());
}
