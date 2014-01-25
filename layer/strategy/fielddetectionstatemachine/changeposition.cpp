#include "layer/strategy/fielddetectionstatemachine/changeposition.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/autonomous/robot.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;

ChangePosition::ChangePosition(Autonomous::Robot &robot, Autonomous::Field &field, Strategy::Common::Referee &referee, Logger &logger):
	State(robot, field, referee, logger, true)
{ }

RoboHockey::Layer::Strategy::Common::State *ChangePosition::nextState()
{
	if (m_robot.reachedTarget() || m_robot.cantReachTarget())
		return new DetectField(m_robot, m_field, m_referee, m_logger, 0);
	else
		return 0;
}

string ChangePosition::getName()
{
	return "ChangePosition";
}

void ChangePosition::updateInternal()
{
	m_robot.leaveCollectedPuck();
}

