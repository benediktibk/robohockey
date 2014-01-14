#include "layer/strategy/mainstatemachine/initialstatetest.h"
#include "layer/strategy/mainstatemachine/initialstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void InitialStateTest::nextState_detectionStart_calibrate()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	InitialState initialState(robot, field, referee, logger);
	referee.setDetectionStart(true);
	referee.setGameStart(true);
	State *state;

	state = initialState.nextState();

	Calibrate *stateCasted = dynamic_cast<Calibrate*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void InitialStateTest::nextState_gameStartAndNotDetectionStart_notCalibrate()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	InitialState initialState(robot, field, referee, logger);
	referee.setDetectionStart(false);
	referee.setGameStart(true);
	State *state;

	state = initialState.nextState();

	Calibrate *stateCasted = dynamic_cast<Calibrate*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}



