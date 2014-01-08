#include "layer/strategy/mainstatemachine/achievegoalstest.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void AchieveGoalsTest::nextState_stopMovement_pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	AchieveGoals achieveGoals(robot, field, referee);
	referee.setStopMovement(true);
	referee.setDetectionStart(false);
	field.setAchievedGoals(0);
	referee.setGameStart(false);
	referee.setGameOver(false);
	State *state;

	state = achieveGoals.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void AchieveGoalsTest::nextState_gameOver_pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	AchieveGoals achieveGoals(robot, field, referee);
	referee.setStopMovement(false);
	referee.setDetectionStart(false);
	field.setAchievedGoals(0);
	referee.setGameStart(false);
	referee.setGameOver(true);
	State *state;

	state = achieveGoals.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void AchieveGoalsTest::nextState_achievedGoals3_hideEnemyPucks()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	AchieveGoals achieveGoals(robot, field, referee);
	referee.setStopMovement(false);
	referee.setDetectionStart(false);
	field.setAchievedGoals(3);
	referee.setGameStart(false);
	referee.setGameOver(false);
	State *state;

	state = achieveGoals.nextState();

	HideEnemyPucks *stateCasted = dynamic_cast<HideEnemyPucks*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void AchieveGoalsTest::nextState_achievedGoals1_notHideEnemyPucks()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	AchieveGoals achieveGoals(robot, field, referee);
	referee.setStopMovement(false);
	referee.setDetectionStart(false);
	field.setAchievedGoals(1);
	referee.setGameStart(false);
	referee.setGameOver(false);
	State *state;

	state = achieveGoals.nextState();

	HideEnemyPucks *stateCasted = dynamic_cast<HideEnemyPucks*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void AchieveGoalsTest::nextState_achievedGoals1_notPause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	AchieveGoals achieveGoals(robot, field, referee);
	referee.setStopMovement(false);
	referee.setDetectionStart(false);
	field.setAchievedGoals(1);
	referee.setGameStart(false);
	referee.setGameOver(false);
	State *state;

	state = achieveGoals.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void AchieveGoalsTest::nextState_achievedGoals1_AchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	AchieveGoals achieveGoals(robot, field, referee);
	referee.setStopMovement(false);
	referee.setDetectionStart(false);
	field.setAchievedGoals(1);
	referee.setGameStart(false);
	referee.setGameOver(false);
	State *state;

	state = achieveGoals.nextState();

	CPPUNIT_ASSERT(state == 0);
}
