#include "layer/strategy/hideenemypuckstest.h"
#include "layer/strategy/hideenemypucks.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/refereemock.h"
#include "layer/strategy/pause.h"
#include "layer/strategy/achievegoals.h"

using namespace RoboHockey::Layer::Strategy;
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

