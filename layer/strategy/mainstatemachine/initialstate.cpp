#include "layer/strategy/mainstatemachine/initialstate.h"
#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger) :
	State(robot, field, referee, logger, false)
{ }

State* InitialState::nextState()
{
	if(m_referee.detectionStart())
		return new Calibrate(m_robot, m_field, m_referee);
	else
		return 0;
}

string InitialState::getName()
{
	return "Initial";
}

bool InitialState::allowLogMessages()
{
	return false;
}

void InitialState::updateInternal()
{}
