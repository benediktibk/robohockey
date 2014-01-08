#include "layer/strategy/mainstatemachine/drivetofinalpositiontest.h"
#include "layer/strategy/mainstatemachine/drivetofinalposition.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"


using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void DriveToFinalPositionTest::nextState_stopMovement_Pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DriveToFinalPosition driveToFinalPosition(robot, field, referee);
	field.setAchievedGoals(3);
	field.setEnemyHiddenPucks(3);
	referee.setStopMovement(true);
	State *state;

	state = driveToFinalPosition.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToFinalPositionTest::nextState_gameOver_Pause()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DriveToFinalPosition driveToFinalPosition(robot, field, referee);
	field.setAchievedGoals(3);
	field.setEnemyHiddenPucks(3);
	referee.setStopMovement(false);
	referee.setGameOver(true);
	State *state;

	state = driveToFinalPosition.nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToFinalPositionTest::nextState_achieveGoals2_AchieveGoals()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DriveToFinalPosition driveToFinalPosition(robot, field, referee);
	field.setAchievedGoals(2);
	field.setEnemyHiddenPucks(3);
	referee.setStopMovement(false);
	referee.setGameOver(false);
	State *state;

	state = driveToFinalPosition.nextState();

	AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToFinalPositionTest::nextState_notAllEnemyPucksHidden_HideEnemyPucks()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DriveToFinalPosition driveToFinalPosition(robot, field, referee);
	field.setAchievedGoals(3);
	field.setEnemyHiddenPucks(2);
	robot.setReachedTarget(false);
	referee.setStopMovement(false);
	referee.setGameOver(false);
	State *state;

	state = driveToFinalPosition.nextState();

	HideEnemyPucks *stateCasted = dynamic_cast<HideEnemyPucks*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}
