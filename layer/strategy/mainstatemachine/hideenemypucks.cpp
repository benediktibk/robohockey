#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/mainstatemachine/drivetofinalposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/common/drivepucktohidepucks.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

HideEnemyPucks::HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee):
	State(robot, field, referee, false)
{
	DrivePuck *drivePuck = new DrivePuckToHidePucks(m_field);
	State *initialState = new DrivePuckStateMachine::InitialState(robot, field, referee, drivePuck);
	m_drivePuckStateMachine = new StateMachine(initialState, robot, field, referee);
}

HideEnemyPucks::~HideEnemyPucks()
{
	delete m_drivePuckStateMachine;
	m_drivePuckStateMachine = 0;
}

State* HideEnemyPucks::nextState()
{
	if(m_referee.gameOver() || m_referee.stopMovement())
		return new Pause(m_robot, m_field, m_referee);
	else if(m_field.getNumberOfAchievedGoals() < 3)
		return new AchieveGoals(m_robot, m_field, m_referee);
	else if(m_field.getNumberOfHiddenPucks() >= 3)
		return new DriveToFinalPosition(m_robot, m_field, m_referee);
	else
		return 0;
}

std::string HideEnemyPucks::getName() const
{
	return "HideEnemyPucks: " + m_drivePuckStateMachine->getNameOfCurrentState();
}

void HideEnemyPucks::updateInternal()
{
	m_drivePuckStateMachine->update();
}

