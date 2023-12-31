#include "layer/strategy/drivepuckstatemachine/checkpuckcolorstate.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CheckPuckColorState::CheckPuckColorState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee),
	m_drivePuck(drivePuck),
	m_foundPuck(false)
{ }

State* CheckPuckColorState::nextState()
{
	if(m_foundPuck)
		return new CollectPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;
}

void CheckPuckColorState::update()
{
}
