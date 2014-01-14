#include "layer/strategy/mainstatemachine/hideenemypuckstest.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/drivetofinalposition.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void HideEnemyPucksTest::nextState_notAllEnemyPucksHidden_notAchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	HideEnemyPucks hideEnemyPucks(robot, field, referee, logger);
	field.setAchievedGoals(3);
	State *state;

	state = hideEnemyPucks.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void HideEnemyPucksTest::nextState_stopMovement_Pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	HideEnemyPucks hideEnemyPucks(robot, field, referee, logger);
	referee.setGameOver(false);
	referee.setStopMovement(true);
	field.setAchievedGoals(3);
	field.setEnemyHiddenPucks(3);
	State *state;

	state = hideEnemyPucks.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void HideEnemyPucksTest::nextState_gameOver_Pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	HideEnemyPucks hideEnemyPucks(robot, field, referee, logger);
	referee.setGameOver(true);
	referee.setStopMovement(false);
	field.setAchievedGoals(3);
	field.setEnemyHiddenPucks(3);
	State *state;

	state = hideEnemyPucks.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void HideEnemyPucksTest::nextState_allEnemyPucksHidden_DriveToFinalPosition()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	HideEnemyPucks hideEnemyPucks(robot, field, referee, logger);
	referee.setGameOver(false);
	referee.setStopMovement(false);
	field.setAchievedGoals(3);
	field.setEnemyHiddenPucks(3);
	robot.setReachedTarget(true);
	State *state;

	state = hideEnemyPucks.nextState();

	DriveToFinalPosition *stateCasted = dynamic_cast<DriveToFinalPosition*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void HideEnemyPucksTest::nextState_achievedGoals2_AchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	HideEnemyPucks hideEnemyPucks(robot, field, referee, logger);
	referee.setGameOver(false);
	referee.setStopMovement(false);
	field.setAchievedGoals(2);
	field.setEnemyHiddenPucks(3);
	robot.setReachedTarget(true);
	State *state;

	state = hideEnemyPucks.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void HideEnemyPucksTest::nextState_nextState_hideEnemyPucks()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	HideEnemyPucks hideEnemyPucks(robot, field, referee, logger);
	referee.setGameOver(false);
	referee.setStopMovement(false);
	field.setAchievedGoals(2);
	field.setEnemyHiddenPucks(2);
	robot.setReachedTarget(false);
	State *state;

	state = hideEnemyPucks.nextState();

	CPPUNIT_ASSERT(state == 0);
}

