#include "layer/strategy/mainstatemachine/pausetest.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/statemock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;


void PauseTest::nextState_detectionStart_Calibrate()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Pause pause(robot, field, referee, logger);
	referee.setDetectionStart(true);
	referee.setGameStart(false);
	State *state;

	state = pause.nextState();

	Calibrate *stateCasted = dynamic_cast<Calibrate*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PauseTest::nextState_gameStart_AchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Pause pause(robot, field, referee, logger);
	referee.setDetectionStart(false);
	referee.setGameStart(true);
	State *state;

	state = pause.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PauseTest::nextState_achieveGoals2_AchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Pause pause(robot, field, referee, logger);
	referee.setDetectionStart(false);
	referee.setGameStart(false);
	referee.setStopMovement(false);
	referee.setGameOver(false);
	field.setAchievedGoals(2);
	State *state;

	state = pause.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PauseTest::nextState_gameOver_Pause()
{   RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Pause pause(robot, field, referee, logger);
	referee.setDetectionStart(false);
	referee.setGameStart(false);
	referee.setStopMovement(false);
	referee.setGameOver(true);
	field.setAchievedGoals(2);
	State *state;

	state = pause.nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PauseTest::nextState_stopMovement_Pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Pause pause(robot, field, referee, logger);
	referee.setDetectionStart(false);
	referee.setGameStart(false);
	referee.setStopMovement(true);
	referee.setGameOver(false);
	field.setAchievedGoals(2);
	State *state;

	state = pause.nextState();

	CPPUNIT_ASSERT(state == 0);
}
