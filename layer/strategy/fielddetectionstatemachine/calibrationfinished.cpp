#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/robotposition.h"
#include "layer/strategy/common/waitcyclesstate.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;

CalibrationFinished::CalibrationFinished(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, Logger &logger, unsigned int reachedTargets) :
	State(robot, field, referee, logger, false),
	m_reachedTargets(reachedTargets)
{ }

State* CalibrationFinished::nextState()
{
	if (m_reachedTargets >= 3)
		return 0;

	std::list<RobotPosition> targetList;
	targetList.push_back(m_field.getTargetsForWaitingPhase()[m_reachedTargets]);

	return new WaitCyclesState(m_robot, m_field, m_referee, m_logger,
					new DriveToState(m_robot, m_field, m_referee, m_logger, targetList,
					   new CalibrationFinished(m_robot, m_field, m_referee, m_logger, m_reachedTargets +1),
					   new CalibrationFinished(m_robot, m_field, m_referee, m_logger, m_reachedTargets +1)), 15, true);
}

std::string CalibrationFinished::getName()
{
	return "CalibrationFinished";
}

void CalibrationFinished::updateInternal()
{
}
