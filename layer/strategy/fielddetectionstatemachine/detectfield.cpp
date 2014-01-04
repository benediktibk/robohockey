#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/angle.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DetectField::DetectField(Robot &robot, Field &field, Referee &referee, vector<RobotPosition> previousCalibrationResults) :
	State(robot, field, referee, false),
	m_successful(false),
	m_numberOfTries(0),
	m_calibrationResults(previousCalibrationResults)
{ }

State* DetectField::nextState()
{
	if (!m_successful && m_numberOfTries < 3)
		return 0;
	else if (!m_successful || ((size_t) 4 > m_calibrationResults.size()))
		return new TurnAngle(m_robot, m_field, m_referee, Angle::getQuarterRotation(), m_calibrationResults);
	else if (m_field.isCalibrated())
		//! @todo use different state if DriveTo can't reach target!
	{
		return new DriveToState(m_robot, m_field, m_referee, m_field.getTargetsForGoalDetection(),
						   new CheckGoalColor(m_robot, m_field, m_referee),
						   new CheckGoalColor(m_robot, m_field, m_referee));
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
	RobotPosition result = m_field.getNewOriginFromFieldDetection();

	if (!(result == RobotPosition()))
	{
		m_calibrationResults.push_back(result);
		m_successful = true;
	}

	m_numberOfTries++;

	if ((size_t) 4 <= m_calibrationResults.size())
	{
		m_field.transformFieldToNewOrigin(m_calibrationResults.front());
		m_successful = true;
	}
}
