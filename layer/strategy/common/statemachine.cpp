#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/state.h"
#include "layer/autonomous/robot.h"
#include "layer/strategy/common/referee.h"
#include <assert.h>

using namespace std;
using namespace RoboHockey::Layer::Strategy::Common;

StateMachine::StateMachine(State *initialState, Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee) :
	m_currentState(initialState),
	m_robot(robot),
	m_field(field),
	m_referee(referee)
{
	assert(m_currentState != 0);
}

StateMachine::~StateMachine()
{
	delete m_currentState;
	m_currentState = 0;
}

void StateMachine::update()
{
	State *nextState = m_currentState->nextState();

	if (nextState != 0)
	{
		delete m_currentState;
		m_currentState = nextState;
	}

	m_currentState->update();
}

const State &StateMachine::getCurrentState() const
{
	return *m_currentState;
}

string StateMachine::getNameOfCurrentState() const
{
	return m_currentState->getName();
}

bool StateMachine::allowLogMessages() const
{
	return m_currentState->allowLogMessages();
}
