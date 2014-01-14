#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/robot.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CheckGoalColor::CheckGoalColor(Robot &robot, Field &field, Referee &referee, Logger &logger) :
	State(robot, field, referee, logger, false),
	m_teamColorSend(false),
	m_gotResponse(false),
	m_numberOfTries(0)
{ }

State* CheckGoalColor::nextState()
{
	if (m_teamColorSend && m_gotResponse)
		return new CalibrationFinished(m_robot, m_field, m_referee, m_logger, 0);

	return 0;
}

std::string CheckGoalColor::getName()
{
	return "CheckGoalColor";
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
		else if (m_numberOfTries < 5)
			++m_numberOfTries;
		else
		{
			m_referee.tellTeamColor(FieldColorYellow);
			m_teamColorSend = true;
		}
	}

	FieldColor refereeResponse = m_referee.trueColorOfTeam();

	if (refereeResponse != FieldColorUnknown)
	{
		m_field.setTrueTeamColor(refereeResponse);
		m_gotResponse = true;
	}
}
