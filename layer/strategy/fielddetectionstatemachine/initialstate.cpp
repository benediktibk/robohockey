#include "layer/strategy/fielddetectionstatemachine/initialstate.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee, false)
{ }

State* InitialState::nextState()
{
	return new DetectField(m_robot, m_field, m_referee, std::vector<RoboHockey::Common::RobotPosition>());
}

std::string InitialState::getName()
{
	return "Initial";
}

void InitialState::updateInternal()
{}
