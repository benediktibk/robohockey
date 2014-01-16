#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/autonomous/field.h"
#include "common/logger.h"
#include <sstream>
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

WaitCyclesState::WaitCyclesState(Robot &robot, Field &field, Referee &referee, Logger &logger, State *stateAfterWaitCycles, unsigned int cycles, bool shoudwaitTheWholeTime) :
	State(robot, field, referee, logger, false),
	m_stateAfterWaitCycles(stateAfterWaitCycles),
	m_cycles(cycles),
	m_updateCounter(0),
	m_shouldWaitTheWholeTime(shoudwaitTheWholeTime)
{ }

WaitCyclesState::~WaitCyclesState()
{
	delete m_stateAfterWaitCycles;
	m_stateAfterWaitCycles = 0;
}

State *WaitCyclesState::nextState()
{
	assert(m_stateAfterWaitCycles != 0);

	State *result = 0;
	bool shoudWait = false;
	if(!m_shouldWaitTheWholeTime)
		shoudWait = m_field.isPuckcolorDetected();

	if(m_updateCounter >= m_cycles || shoudWait)
	{
		result = m_stateAfterWaitCycles;
		m_stateAfterWaitCycles = 0;
		stringstream stream("wait for ");
		stream << m_updateCounter;
		stream << " cycles";
		m_logger.logToConsoleAndGlobalLogFile(stream.str());
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
