#include "layer/strategy/common/waitstate.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

WaitState::WaitState(Robot &robot, Field &field, Referee &referee, State *stateAfterWaitCycles, unsigned int cycles) :
	State(robot, field, referee, false),
	m_stateAfterWaitCycles(stateAfterWaitCycles),
	m_cycles(cycles),
	m_updateCounter(0)
{ }

State *WaitState::nextState()
{
	if(m_updateCounter < m_cycles)
		return 0;
	else
		return m_stateAfterWaitCycles;
}

void WaitState::updateInternal()
{
	++m_updateCounter;
}

std::string WaitState::getName()
{
	return "WaitState";
}
