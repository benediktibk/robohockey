#include "layer/strategy/common/statemachinetest.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/mainstatemachine/refereemock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void StateMachineTest::update_empty_stateGotAtLeastOneCallToNextState()
{
	RobotMock robot;
	FieldMock field;
    RefereeMock referee;
    StateMock *state = new StateMock(robot, field, referee);
	StateMachine stateMachine(state, robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToNextState() > 0);
}

void StateMachineTest::update_noStateChange_stateGotAtLeastOneCallToUpdate()
{
	RobotMock robot;
	FieldMock field;
    RefereeMock referee;
    StateMock *state = new StateMock(robot, field, referee);
	StateMachine stateMachine(state, robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToUpdate() > 0);
}

void StateMachineTest::update_empty_robotGotNoCallsToUpdateSensorData()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
    StateMachine stateMachine(new StateMock(robot, field, referee), robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(robot.getCallsToUpdateSensorData() == 0);
}

void StateMachineTest::update_empty_robotGotNoCallsToUpdateActuators()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
    StateMachine stateMachine(new StateMock(robot, field, referee), robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(robot.getCallsToUpdateActuators() == 0);
}

void StateMachineTest::update_stateChange_currentStateIsNewOne()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
    StateMock *oldState = new StateMock(robot, field, referee);
    StateMock *newState = new StateMock(robot, field, referee);
	oldState->setNextState(newState);
	StateMachine stateMachine(oldState, robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(newState == &(stateMachine.getCurrentState()));
}

void StateMachineTest::update_stateChange_currentStateGotAtLeastOneCallToUpdate()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
    StateMock *oldState = new StateMock(robot, field, referee);
    StateMock *newState = new StateMock(robot, field, referee);
	oldState->setNextState(newState);
	StateMachine stateMachine(oldState, robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(newState->getCallsToUpdate() > 0);
}
