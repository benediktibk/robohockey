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
	State(robot, field, referee, false),
	m_teamColorSend(false),
	m_gotResponse(false)
{ }

State* CheckGoalColor::nextState()
{
	//! @todo Replace Target Point with target point from field.
	if (m_teamColorSend && m_gotResponse)
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

void CheckGoalColor::updateInternal()
{
	if (!m_teamColorSend)
	{
		m_field.detectTeamColorWithGoalInFront();

		if (m_field.getOwnTeamColor() != FieldColorUnknown)
		{
			m_referee.tellTeamColor(m_field.getOwnTeamColor());
			m_teamColorSend = true;
		}
	}

	FieldColor refResponse = FieldColorUnknown;
	refResponse = m_referee.trueColorOfTeam();

	if (refResponse != FieldColorUnknown)
	{
		m_field.setTrueTeamColor(refResponse);
		m_gotResponse = true;
	}

}
