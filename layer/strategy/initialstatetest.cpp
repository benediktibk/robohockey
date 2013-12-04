#include "layer/strategy/initialstatetest.h"
#include "layer/strategy/initialstate.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

void InitialStateTest::update_empty_stateGotAtLeastOneCallToNextState()
{
    RobotMock robot;
    FieldMock field;
    StateMock state(robot, field);
    InitialState initialState(robot, field);

    initialState.update();

    CPPUNIT_ASSERT(state.getCallsToNextState() > 0);
}
