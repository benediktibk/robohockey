#include "layer/strategy/fielddetectionstatemachine/calibrationfinishedtest.h"
#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/waitstate.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;


void CalibrationFinishedTest::nextState_3TargetsReached_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CalibrationFinished calibrationFinishedState(robot, field, referee, 3);

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
	CalibrationFinished calibrationFinishedState(robot, field, referee, 0);

	calibrationFinishedState.update();

	State *state;
	state = calibrationFinishedState.nextState();
	WaitState *stateCasted = dynamic_cast<WaitState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void CalibrationFinishedTest::nextState_1TargetsReached_WaitState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CalibrationFinished calibrationFinishedState(robot, field, referee, 1);

	calibrationFinishedState.update();

	State *state;
	state = calibrationFinishedState.nextState();
	WaitState *stateCasted = dynamic_cast<WaitState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}
