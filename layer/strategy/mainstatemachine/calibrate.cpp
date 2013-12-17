#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/common/referee.h"
#include "layer/strategy/fielddetectionstatemachine/initialstate.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

Calibrate::Calibrate(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee)
{
	State *initialState = new FieldDetectionStateMachine::InitialState(robot, field, referee);
	m_fieldDetectionStateMachine = new StateMachine(initialState, robot, field, referee);

}

Calibrate::~Calibrate()
{
	delete m_fieldDetectionStateMachine;
	m_fieldDetectionStateMachine = 0;
}

State* Calibrate::nextState()
{
	if(m_referee.gameStart())
	{
		return new AchieveGoals(m_robot, m_field, m_referee);
	}
	else if(m_referee.stopMovement() || m_referee.gameOver())
	{
		return new Pause(m_robot, m_field, m_referee);
	}
	return 0;
}

void Calibrate::update()
{
	m_fieldDetectionStateMachine->update();
}




