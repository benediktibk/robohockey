#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/angle.h"
#include <boost/bind.hpp>
#include <algorithm>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DetectField::DetectField(Robot &robot, Field &field, Referee &referee, list<pair<unsigned int, RobotPosition> > previousCalibrationResults) :
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
	unsigned int numberOfStones = 0;
	RobotPosition result = m_field.getNewOriginFromFieldDetection(numberOfStones);

	if (!(result == RobotPosition()))
	{
		if (numberOfStones >= m_calibrationResults.front().first)
			m_calibrationResults.push_front(pair<unsigned int, RoboHockey::Common::RobotPosition>(numberOfStones, result));
		else
			m_calibrationResults.push_back(pair<unsigned int, RoboHockey::Common::RobotPosition>(numberOfStones, result));

		m_successful = true;
	}

	m_numberOfTries++;

	if ((size_t) 4 <= m_calibrationResults.size())
	{
		m_field.transformFieldToNewOrigin(m_calibrationResults.front().second);
		m_successful = true;
	}
}
