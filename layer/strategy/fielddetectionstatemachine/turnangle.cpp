#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "common/angle.h"
#include "common/point.h"
#include "common/robotposition.h"
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

TurnAngle::TurnAngle(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, Angle angle, std::vector<RobotPosition> calibratedPositions) :
	State(robot, field, referee, true),
	m_angle(angle),
	m_calibratedPositions(calibratedPositions)
{ }

State* TurnAngle::nextState()
{
	if (m_robot.reachedTarget())
		return new DetectField(m_robot, m_field, m_referee, m_calibratedPositions);
	else
		return 0;
}

std::string TurnAngle::getName()
{
	return "TurnAngle";
}

void TurnAngle::updateInternal()
{
	Point target(1, 0);
	target.rotate(m_robot.getCurrentPosition().getOrientation() + m_angle);
	m_robot.turnTo(target);
}
