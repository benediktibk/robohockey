#include "layer/strategy/statemachine.h"
#include "layer/strategy/state.h"
#include "layer/autonomous/robot.h"
#include "layer/strategy/referee.h"

#include <assert.h>

using namespace RoboHockey::Layer::Strategy;

StateMachine::StateMachine(State *initialState, Autonomous::Robot *robot, Autonomous::Field *field, Referee *referee) :
	m_currentState(initialState),
    m_robot(robot),
    m_field(field),
    m_referee(referee)
{
	assert(m_currentState != 0);
	assert(m_robot != 0);
    assert(m_referee != 0);
}

StateMachine::~StateMachine()
{
	delete m_currentState;
	m_currentState = 0;
	delete m_robot;
	m_robot = 0;
    delete m_referee;
    m_referee = 0;
}

void StateMachine::update()
{
	m_robot->updateSensorData();

	State *nextState = m_currentState->nextState();

	if (nextState != 0)
	{
		delete m_currentState;
		m_currentState = nextState;
	}

	m_currentState->update();
	m_robot->updateActuators();;
}

const State &StateMachine::getCurrentState() const
{
	return *m_currentState;
}
