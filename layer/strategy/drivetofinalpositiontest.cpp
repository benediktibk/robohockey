#include "layer/strategy/drivetofinalpositiontest.h"
#include "layer/strategy/drivetofinalposition.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/refereemock.h"
#include "layer/strategy/pause.h"
#include "layer/strategy/hideenemypucks.h"
#include "layer/strategy/achievegoals.h"


using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

void DriveToFinalPositionTest::nextState_stopMovement_pause()
{
    RobotMock robot;
    FieldMock field;
    RefereeMock referee;
    HideEnemyPucks hideEnemyPucks(robot, field, referee);
    field.setAchievedGoals(3);
    field.setEnemyHiddenPucks(3);
    referee.setStopMovement(true);
    State *state;
    state = hideEnemyPucks.nextState();
    Pause *stateCasted = dynamic_cast<Pause*>(state);
    CPPUNIT_ASSERT(stateCasted != 0);
}
