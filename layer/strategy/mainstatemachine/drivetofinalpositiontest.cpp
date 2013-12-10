#include "layer/strategy/mainstatemachine/drivetofinalpositiontest.h"
#include "layer/strategy/mainstatemachine/drivetofinalposition.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/mainstatemachine/refereemock.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"


using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
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
