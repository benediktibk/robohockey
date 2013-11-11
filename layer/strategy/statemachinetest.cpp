#include "layer/strategy/statemachinetest.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/statemock.h"
#include "layer/autonomous/robotmock.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

void StateMachineTest::update_empty_stateGotAtLeastOneCallToNextState()
{
	RobotMock *robot = new RobotMock;
	StateMock *state = new StateMock(*robot);
	StateMachine stateMachine(state, robot);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToNextState() > 0);
}

void StateMachineTest::update_noStateChange_stateGotAtLeastOneCallToUpdate()
{
	RobotMock *robot = new RobotMock;
	StateMock *state = new StateMock(*robot);
	StateMachine stateMachine(state, robot);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToUpdate() > 0);
}

void StateMachineTest::update_empty_robotGotAtLeastOneCallToUpdateSensorData()
{
	RobotMock *robot = new RobotMock;
	StateMachine stateMachine(new StateMock(*robot), robot);

	stateMachine.update();

	CPPUNIT_ASSERT(robot->getCallsToUpdateSensorData() > 0);
}

void StateMachineTest::update_empty_robotGotAtLeastOneCallToUpdateActuators()
{
	RobotMock *robot = new RobotMock;
	StateMachine stateMachine(new StateMock(*robot), robot);

	stateMachine.update();

	CPPUNIT_ASSERT(robot->getCallsToUpdateActuators() > 0);
}

void StateMachineTest::update_stateChange_currentStateIsNewOne()
{
	RobotMock *robot = new RobotMock;
	StateMock *oldState = new StateMock(*robot);
	StateMock *newState = new StateMock(*robot);
	oldState->setNextState(newState);
	StateMachine stateMachine(oldState, robot);

	stateMachine.update();

	CPPUNIT_ASSERT(newState == &(stateMachine.getCurrentState()));
}

void StateMachineTest::update_stateChange_currentStateGotAtLeastOneCallToUpdate()
{
	RobotMock *robot = new RobotMock;
	StateMock *oldState = new StateMock(*robot);
	StateMock *newState = new StateMock(*robot);
	oldState->setNextState(newState);
	StateMachine stateMachine(oldState, robot);

	stateMachine.update();

	CPPUNIT_ASSERT(newState->getCallsToUpdate() > 0);
}
