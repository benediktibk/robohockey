#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/common/driveto.h"
#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/robot.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CheckGoalColor::CheckGoalColor(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee),
	m_successful(false)
{ }

State* CheckGoalColor::nextState()
{
	//! @todo Replace Target Point with target point from field.
	if (m_successful)
	{
		std::list<RobotPosition> targetList;
		targetList.push_back(RobotPosition(Point(5.0/6.0, 1.5), Angle()));

		return new DriveTo(m_robot, m_field, m_referee,
						   targetList,
						   new CalibrationFinished(m_robot, m_field, m_referee),
						   new CalibrationFinished(m_robot, m_field, m_referee));
	}
	return 0;
}

void CheckGoalColor::update()
{
	m_field.detectTeamColorWithGoalInFront();
	m_successful = (m_field.getOwnTeamColor() != FieldColorUnknown);
}
