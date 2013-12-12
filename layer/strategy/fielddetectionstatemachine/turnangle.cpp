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

TurnAngle::TurnAngle(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, Angle angle) :
	State(robot, field, referee),
	m_angle(angle),
	m_targetSet(false)
{ }

State* TurnAngle::nextState()
{
	assert(m_targetSet);

	if (m_robot.reachedTarget())
		return new DetectField(m_robot, m_field, m_referee);
	else
		return 0;
}

void TurnAngle::update()
{
	if (!m_targetSet)
	{
		Point target(1, 0);
		target.rotate(m_robot.getCurrentPosition().getOrientation() + m_angle);
		m_robot.turnTo(target);
		m_targetSet = true;
	}
}
