#include "layer/strategy/mainstatemachine/hideenemypuckstest.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/mainstatemachine/refereemock.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void HideEnemyPucksTest::nextState_notAllEnemyPucksHidden_notAchieveGoals()
{
    RobotMock robot;
    FieldMock field;
    RefereeMock referee;
    HideEnemyPucks hideEnemyPucks(robot, field, referee);
    field.setAchievedGoals(3);
    State *state;
    state = hideEnemyPucks.nextState();
    AchieveGoals *stateCasted = dynamic_cast<AchieveGoals*>(state);
    CPPUNIT_ASSERT(stateCasted == 0);
}

