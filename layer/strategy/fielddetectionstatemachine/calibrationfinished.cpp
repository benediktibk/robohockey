#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/robotposition.h"
#include "layer/strategy/common/waitstate.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;

CalibrationFinished::CalibrationFinished(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, unsigned int reachedTargets) :
	State(robot, field, referee, false),
	m_reachedTargets(reachedTargets)
{ }

State* CalibrationFinished::nextState()
{
	if (m_reachedTargets >= 3)
		return 0;

	std::list<RobotPosition> targetList;
	targetList.push_back(m_field.getTargetsForWaitingPhase()[m_reachedTargets]);

	return new WaitState(m_robot, m_field, m_referee,
					new DriveToState(m_robot, m_field, m_referee, targetList,
					   new CalibrationFinished(m_robot, m_field, m_referee, m_reachedTargets +1),
					   new CalibrationFinished(m_robot, m_field, m_referee, m_reachedTargets +1)), 10);
}

std::string CalibrationFinished::getName()
{
	return "CalibrationFinished";
}

void CalibrationFinished::updateInternal()
{
}
