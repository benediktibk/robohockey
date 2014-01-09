#include "layer/strategy/common/waitcyclesstatetest.h"
#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

void WaitCyclesStateTest::nextState_didntWaitEnoughCycles_resultIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterWaitCycles = new StateMock(robot, field, referee);
	WaitCyclesState waitState(robot, field, referee, stateAfterWaitCycles, 10);
	waitState.update();
	waitState.update();
	waitState.update();
	waitState.update();

	State *state = waitState.nextState();

	CPPUNIT_ASSERT(state == 0);
}

void WaitCyclesStateTest::nextState_didWaitEnoughCycles_resultIsStateAfterWaitCycles()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterWaitCycles = new StateMock(robot, field, referee);
	WaitCyclesState waitState(robot, field, referee, stateAfterWaitCycles, 5);

	waitState.update();
	waitState.update();
	waitState.update();
	waitState.update();
	waitState.update();

	State *state = waitState.nextState();

	CPPUNIT_ASSERT(state == stateAfterWaitCycles);
	delete state;
}
