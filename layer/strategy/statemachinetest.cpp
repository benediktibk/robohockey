#include "layer/strategy/statemachinetest.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/refereemock.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

void StateMachineTest::update_empty_stateGotAtLeastOneCallToNextState()
{
	RobotMock robot;
	FieldMock field;
	StateMock *state = new StateMock(robot, field);
	RefereeMock referee;
	StateMachine stateMachine(state, robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToNextState() > 0);
}

void StateMachineTest::update_noStateChange_stateGotAtLeastOneCallToUpdate()
{
	RobotMock robot;
	FieldMock field;
	StateMock *state = new StateMock(robot, field);
	RefereeMock referee;
	StateMachine stateMachine(state, robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToUpdate() > 0);
}

void StateMachineTest::update_empty_robotGotAtLeastOneCallToUpdateSensorData()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	StateMachine stateMachine(new StateMock(robot, field), robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(robot.getCallsToUpdateSensorData() > 0);
}

void StateMachineTest::update_empty_robotGotAtLeastOneCallToUpdateActuators()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	StateMachine stateMachine(new StateMock(robot, field), robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(robot.getCallsToUpdateActuators() > 0);
}

void StateMachineTest::update_stateChange_currentStateIsNewOne()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	StateMock *oldState = new StateMock(robot, field);
	StateMock *newState = new StateMock(robot, field);
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
	StateMock *oldState = new StateMock(robot, field);
	StateMock *newState = new StateMock(robot, field);
	oldState->setNextState(newState);
	StateMachine stateMachine(oldState, robot, field, referee);

	stateMachine.update();

	CPPUNIT_ASSERT(newState->getCallsToUpdate() > 0);
}
