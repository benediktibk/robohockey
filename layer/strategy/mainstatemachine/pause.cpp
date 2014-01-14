#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

Pause::Pause(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger) :
	State(robot, field, referee, logger, true)
{}

State* Pause::nextState()
{
	if(m_referee.gameStart())
		return new AchieveGoals(m_robot, m_field, m_referee, m_logger);
	else if(m_referee.detectionStart())
		return new Calibrate(m_robot, m_field, m_referee, m_logger);
	else if(m_field.getNumberOfAchievedGoals() < 3 && not m_referee.stopMovement() && not m_referee.gameOver())
		return new AchieveGoals(m_robot, m_field, m_referee, m_logger);
	else
		return 0;
}

string Pause::getName()
{
	return "Pause";
}

bool Pause::allowLogMessages()
{
	return false;
}

void Pause::updateInternal()
{
	m_robot.stop();
}

