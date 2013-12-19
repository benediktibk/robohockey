#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/common/driveto.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/angle.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DetectField::DetectField(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee, false),
	m_successful(false),
	m_numberOfTries(0)
{ }

State* DetectField::nextState()
{
	if (!m_successful && m_numberOfTries < 3)
		return 0;
	else if (!m_successful)
		return new TurnAngle(m_robot, m_field, m_referee, Angle::getEighthRotation());
	else
		//! @todo use different state if DriveTo can't reach target!
	{
		return new DriveTo(m_robot, m_field, m_referee, m_field.getTargetsForGoalDetection(),
						   new CheckGoalColor(m_robot, m_field, m_referee),
						   new CheckGoalColor(m_robot, m_field, m_referee));
	}
}

void DetectField::updateInternal()
{
	m_successful = m_field.calibratePosition();
	m_numberOfTries++;
}
