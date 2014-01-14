#include "layer/strategy/fielddetectionstatemachine/calibrationfinishedtest.h"
#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;

void CalibrationFinishedTest::nextState_3TargetsReached_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	CalibrationFinished calibrationFinishedState(robot, field, referee, logger, 3);

	calibrationFinishedState.update();

	State *state;
	state = calibrationFinishedState.nextState();
	CPPUNIT_ASSERT(state == 0);
}

void CalibrationFinishedTest::nextState_0TargetsReached_WaitState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	CalibrationFinished calibrationFinishedState(robot, field, referee, logger, 0);

	calibrationFinishedState.update();

	State *state;
	state = calibrationFinishedState.nextState();
	WaitCyclesState *stateCasted = dynamic_cast<WaitCyclesState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CalibrationFinishedTest::nextState_1TargetsReached_WaitState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	CalibrationFinished calibrationFinishedState(robot, field, referee, logger, 1);

	calibrationFinishedState.update();

	State *state;
	state = calibrationFinishedState.nextState();
	WaitCyclesState *stateCasted = dynamic_cast<WaitCyclesState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}
