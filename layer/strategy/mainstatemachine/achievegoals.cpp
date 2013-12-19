#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/common/drivepucktoachivegoals.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

AchieveGoals::AchieveGoals(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee, false)
{
	DrivePuck *drivePuck = new DrivePuckToAchiveGoals();
	State *initialState = new DrivePuckStateMachine::InitialState(robot, field, referee, drivePuck);
	m_drivePuckStateMachine = new StateMachine(initialState, robot, field, referee);
}

AchieveGoals::~AchieveGoals()
{
	delete m_drivePuckStateMachine;
	m_drivePuckStateMachine = 0;
}

State* AchieveGoals::nextState()
{
	if(m_referee.stopMovement() || m_referee.gameOver())
		return new Pause(m_robot, m_field, m_referee);
	else if(m_field.getNumberOfAchievedGoals() < 3)
		return 0;
	else
		return new HideEnemyPucks(m_robot, m_field, m_referee);
}

void AchieveGoals::updateInternal()
{
	m_drivePuckStateMachine->update();
}
