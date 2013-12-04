#include "layer/strategy/initialstatetest.h"
#include "layer/strategy/initialstate.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/refereemock.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

void InitialStateTest::update_empty_stateGotAtLeastOneCallToNextState()
{
    RobotMock robot;
    FieldMock field;
    RefereeMock referee;
    StateMock state(robot, field, referee);
    InitialState initialState(robot, field, referee);

    initialState.update();

    CPPUNIT_ASSERT(state.getCallsToNextState() > 0);
}
