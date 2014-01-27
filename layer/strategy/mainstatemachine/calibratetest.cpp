#include "layer/strategy/mainstatemachine/calibratetest.h"
#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/initialstate.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void CalibrateTest::nextState_gameStartAndCalibratedAndTeamColorKnown_achieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(false);
	referee.setGameOver(false);
	referee.setStopMovement(false);

	field.setCalibrationReturn(true);
	field.setTrueTeamColor(FieldColorYellow);
	State *state;

	state = calibrate.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CalibrateTest::nextState_detectionStart_notAchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(false);
	referee.setDetectionStart(true);
	referee.setGameOver(false);
	referee.setStopMovement(false);
	State *state;

	state = calibrate.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
	delete state;
}

void CalibrateTest::nextState_gameStartAndStopMovement_notInitialState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(false);
	referee.setGameOver(false);
	referee.setStopMovement(true);
	State *state;

	state = calibrate.nextState();

	InitialState *stateCasted = dynamic_cast<InitialState*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
	delete state;
}

void CalibrateTest::nextState_gameOverAndStopMovement_pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(false);
	referee.setDetectionStart(false);
	referee.setGameOver(true);
	referee.setStopMovement(true);
	State *state;

	state = calibrate.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CalibrateTest::nextState_gameStartAndGameOver_notInitialState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(false);
	referee.setGameOver(true);
	referee.setStopMovement(false);
	State *state;

	state = calibrate.nextState();

	InitialState *stateCasted = dynamic_cast<InitialState*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
	delete state;
}

void CalibrateTest::nextState_detectionStart_notPause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(false);
	referee.setDetectionStart(true);
	referee.setGameOver(false);
	referee.setStopMovement(false);
	State *state;

	state = calibrate.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void CalibrateTest::nextState_detectionStartAndGameStart_AchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(true);
	referee.setGameOver(false);
	referee.setStopMovement(false);

	field.setCalibrationReturn(true);
	field.setTrueTeamColor(FieldColorBlue);
	State *state;

	state = calibrate.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CalibrateTest::nextState_gameStartAndGameOver_notCalibrate()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(false);
	referee.setGameOver(true);
	referee.setStopMovement(false);
	State *state;

	state = calibrate.nextState();

	Calibrate *stateCasted = dynamic_cast<Calibrate*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
	delete state;
}

void CalibrateTest::nextState_gameStartAndDetectionStartButNotCalibrated_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(true);
	referee.setGameOver(false);
	referee.setStopMovement(false);

	field.setCalibrationReturn(false);
	State *state;

	state = calibrate.nextState();

	CPPUNIT_ASSERT(state == 0);
	delete state;
}

void CalibrateTest::nextState_gameStartAndDetectionStartAndCalibratedButNoTeamColorKnown_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(true);
	referee.setGameOver(false);
	referee.setStopMovement(false);

	field.setCalibrationReturn(true);
	State *state;

	state = calibrate.nextState();

	CPPUNIT_ASSERT(state == 0);
	delete state;
}

void CalibrateTest::nextState_gameStartAndDetectionStartAndTeamColorKnownOnSecondTry_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(true);
	referee.setDetectionStart(true);
	referee.setGameOver(false);
	referee.setStopMovement(false);

	field.setCalibrationReturn(true);
	State *state;
	state = calibrate.nextState();

	CPPUNIT_ASSERT(state == 0);

	field.setTrueTeamColor(FieldColorYellow);
	state = calibrate.nextState();
	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);

	delete state;

}

void CalibrateTest::nextState_stopMovement_pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(false);
	referee.setDetectionStart(false);
	referee.setGameOver(false);
	referee.setStopMovement(true);
	State *state;

	state = calibrate.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CalibrateTest::nextState_gameOver_pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	Calibrate calibrate(robot, field, referee, logger);
	referee.setGameStart(false);
	referee.setDetectionStart(false);
	referee.setGameOver(true);
	referee.setStopMovement(false);
	State *state;

	state = calibrate.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}
