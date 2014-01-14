#include "layer/strategy/common/state.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

State::State(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, bool callUpdateOnlyOnce) :
	m_robot(robot),
	m_field(field),
	m_referee(referee),
	m_logger(logger),
	m_callUpdateOnlyOnce(callUpdateOnlyOnce),
	m_updateAlreadyCalled(false)
{ }

State::~State()
{ }

void State::update()
{
	if (!(m_updateAlreadyCalled && m_callUpdateOnlyOnce))
		updateInternal();

	m_updateAlreadyCalled = true;
}

bool State::allowLogMessages()
{
	return true;
}
