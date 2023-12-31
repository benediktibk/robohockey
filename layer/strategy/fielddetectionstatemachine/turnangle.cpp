#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "common/angle.h"
#include "common/point.h"
#include "common/robotposition.h"
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

TurnAngle::TurnAngle(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, Logger &logger, Angle angle,
					 unsigned int numberOfTurns) :
	State(robot, field, referee, logger,  true),
	m_angle(angle),
	m_numberOfTurns(numberOfTurns)
{ }

State* TurnAngle::nextState()
{
	if (m_robot.reachedTarget())
		return new DetectField(m_robot, m_field, m_referee, m_logger, m_numberOfTurns);
	else
		return 0;
}

std::string TurnAngle::getName()
{
	return "TurnAngle";
}

void TurnAngle::updateInternal()
{
	Point target(1,0);
	target.rotate(m_robot.getCurrentPosition().getOrientation() + m_angle);
	target = target + m_robot.getCurrentPosition().getPosition();
	m_robot.turnTo(target);
}
