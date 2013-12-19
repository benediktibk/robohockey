#include "layer/strategy/common/statemock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

StateMock::StateMock(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee, false),
	m_callsToNextState(0),
	m_callsToUpdate(0),
	m_nextState(0)
{ }

StateMock::StateMock(Robot &robot, Field &field, Referee &referee, bool callUpdateOnlyOnce) :
	State(robot, field, referee, callUpdateOnlyOnce),
	m_callsToNextState(0),
	m_callsToUpdate(0),
	m_nextState(0)
{ }

State *StateMock::nextState()
{
	++m_callsToNextState;
	return m_nextState;
}

void StateMock::updateInternal()
{
	++m_callsToUpdate;
}

unsigned int StateMock::getCallsToNextState() const
{
	return m_callsToNextState;
}

unsigned int StateMock::getCallsToUpdate() const
{
	return m_callsToUpdate;
}

void StateMock::setNextState(State *state)
{
	m_nextState = state;
}
