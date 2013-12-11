#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/angle.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DetectField::DetectField(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee)
{ }

State* DetectField::nextState()
{
	if (m_field.calibratePosition())
		return 0;
	else
		return new TurnAngle(m_robot, m_field, m_referee, Angle::getEighthRotation());
}

void DetectField::update()
{}
