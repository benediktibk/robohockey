#include "layer/strategy/achievegoalstest.h"
#include "layer/strategy/achievegoals.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/refereemock.h"
#include "layer/strategy/pause.h"
#include "layer/strategy/hideenemypucks.h"

using namespace RoboHockey::Layer::Strategy;
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
