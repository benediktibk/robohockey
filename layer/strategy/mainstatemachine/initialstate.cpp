#include "layer/strategy/mainstatemachine/initialstate.h"
#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee, false)
{ }

State* InitialState::nextState()
{
	if(m_referee.detectionStart())
		return new Calibrate(m_robot, m_field, m_referee);
	else
		return 0;
}

std::string InitialState::getName()
{
	return "InitialState";
}

void InitialState::updateInternal()
{}
