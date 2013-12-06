#include "layer/strategy/initialstatetest.h"
#include "layer/strategy/initialstate.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/refereemock.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

void InitialStateTest::nextState_detectionStart_calibrate()
{
    RobotMock robot;
    FieldMock field;
    RefereeMock referee;
    InitialState initialState(robot, field, referee);
    referee.setDetectionStart(true);
    referee.setGameStart(true);
    State *state;
    state = initialState.nextState();
    Calibrate *stateCasted = dynamic_cast<Calibrate*>(state);
    CPPUNIT_ASSERT(stateCasted != 0);
}

void InitialStateTest::nextState_gameStartAndDetectionStart_calibrate()
{
    RobotMock robot;
    FieldMock field;
    RefereeMock referee;
    InitialState initialState(robot, field, referee);
    referee.setDetectionStart(false);
    referee.setGameStart(true);
    State *state;
    state = initialState.nextState();
    Calibrate *stateCasted = dynamic_cast<Calibrate*>(state);
    CPPUNIT_ASSERT(stateCasted == 0);
}



