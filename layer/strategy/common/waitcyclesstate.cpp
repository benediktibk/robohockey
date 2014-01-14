#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/autonomous/field.h"
#include "common/logger.h"
#include <sstream>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

WaitCyclesState::WaitCyclesState(Robot &robot, Field &field, Referee &referee, Logger &logger, State *stateAfterWaitCycles, unsigned int cycles) :
	State(robot, field, referee, logger, false),
	m_stateAfterWaitCycles(stateAfterWaitCycles),
	m_cycles(cycles),
	m_updateCounter(0)
{ }

WaitCyclesState::~WaitCyclesState()
{
	delete m_stateAfterWaitCycles;
	m_stateAfterWaitCycles = 0;
}

State *WaitCyclesState::nextState()
{
	State *result = 0;

	if(m_updateCounter >= m_cycles || m_field.isPuckcolorDetected())
	{
		result = m_stateAfterWaitCycles;
		m_stateAfterWaitCycles = 0;
		stringstream stream("wait for ");
		stream << m_updateCounter;
		stream << " cycles";
		m_logger.logToConsole(stream.str());
	}

	return result;
}

void WaitCyclesState::updateInternal()
{
	++m_updateCounter;
}

string WaitCyclesState::getName()
{
	return "WaitState";
}
