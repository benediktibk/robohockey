#include "layer/strategy/common/waitstate.h"

using namespace std;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

WaitState::WaitState(Robot &robot, Field &field, Referee &referee, State *stateAfterWaitCycles, unsigned int cycles) :
	State(robot, field, referee, false),
	m_stateAfterWaitCycles(stateAfterWaitCycles),
	m_cycles(cycles),
	m_updateCounter(0)
{ }

WaitState::~WaitState()
{
	delete m_stateAfterWaitCycles;
	m_stateAfterWaitCycles = 0;
}

State *WaitState::nextState()
{
	State *result = 0;

	if(m_updateCounter >= m_cycles)
	{
		result = m_stateAfterWaitCycles;
		m_stateAfterWaitCycles = 0;
	}

	return result;
}

void WaitState::updateInternal()
{
	++m_updateCounter;
}

string WaitState::getName()
{
	return "WaitState";
}
