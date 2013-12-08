#include "layer/strategy/achievegoalstest.h"
#include "layer/strategy/achievegoals.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/refereemock.h"
#include "layer/strategy/pause.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

void AchieveGoalsTest::nextState_stopMovement_pause()
{
    RobotMock robot;
    FieldMock field;
    RefereeMock referee;
    AchieveGoals achieveGoals(robot, field, referee);
    referee.setStopMovement(true);
    referee.setDetectionStart(true);
    field.setAchievedGoals(0);
    referee.setGameStart(false);
    referee.setGameOver(true);
    State *state;
    state = achieveGoals.nextState();
    Pause *stateCasted = dynamic_cast<Pause*>(state);
    CPPUNIT_ASSERT(stateCasted == 0);
}
