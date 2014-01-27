#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/fielddetectionstatemachine/initialstate.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

Calibrate::Calibrate(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger) :
	State(robot, field, referee, logger, false)
{
	State *initialState = new FieldDetectionStateMachine::InitialState(robot, field, referee, logger);
	m_fieldDetectionStateMachine = new StateMachine(initialState, robot, field, referee);
}

Calibrate::~Calibrate()
{
	delete m_fieldDetectionStateMachine;
	m_fieldDetectionStateMachine = 0;
}

State* Calibrate::nextState()
{
	if(m_referee.gameStart() && m_field.isCalibrated() && m_field.getOwnTeamColor() != FieldColorUnknown)
	{
		return new AchieveGoals(m_robot, m_field, m_referee, m_logger);
	}
	else if(m_referee.stopMovement() || m_referee.gameOver())
	{
		return new Pause(m_robot, m_field, m_referee, m_logger);
	}
	return 0;
}

std::string Calibrate::getName()
{
	return "Calibrate: " + m_fieldDetectionStateMachine->getNameOfCurrentState();
}

void Calibrate::updateInternal()
{
	m_fieldDetectionStateMachine->update();
}




