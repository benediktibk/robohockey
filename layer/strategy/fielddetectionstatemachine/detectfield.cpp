#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/angle.h"
#include "common/logger.h"
#include <boost/bind.hpp>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DetectField::DetectField(Robot &robot, Field &field, Referee &referee, Logger &logger, unsigned int numberOfTurns) :
	State(robot, field, referee, logger, false),
	m_successful(false),
	m_numberOfTries(0),
	m_numberOfTurns(numberOfTurns)
{ }

State* DetectField::nextState()
{
	if (!m_successful && m_numberOfTries < 3)
		return 0;
	else if (!m_successful)
		return new TurnAngle(m_robot, m_field, m_referee, m_logger,  Angle::convertFromDegreeToRadiant(100), m_calibrationResults);
	else if (m_field.isCalibrated())
		//! @todo use different state if DriveTo can't reach target!
	{
		return new DriveToState(m_robot, m_field, m_referee, m_logger, m_field.getTargetsForGoalDetection(),
							new CheckGoalColor(m_robot, m_field, m_referee, m_logger),
							new CheckGoalColor(m_robot, m_field, m_referee, m_logger),
							new CheckGoalColor(m_robot, m_field, m_referee, m_logger));
	}
	else
		return 0;
}

string DetectField::getName()
{
	return "DetectField";
}

void DetectField::updateInternal()
{
	unsigned int numberOfStones = 0;
	RobotPosition result = m_field.getNewOriginFromFieldDetection(numberOfStones, true);

	if (!(result == RobotPosition()))
		m_successful = true;

	m_numberOfTries++;

	if (m_successful)
	{
		stringstream message;
		message << "Transforming to Position: " << m_calibrationResults.front().second;
		m_logger.logToLogFileOfType(Logger::LogFileTypeStateChanges, message.str());
		m_field.transformFieldToNewOrigin(result);
		m_successful = true;
	}
}
