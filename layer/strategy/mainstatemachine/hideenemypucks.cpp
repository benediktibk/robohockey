#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/mainstatemachine/drivetofinalposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/robot.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/common/colordependentpucktargetfetchertohidepucks.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

HideEnemyPucks::HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee, RoboHockey::Common::Logger &logger):
	State(robot, field, referee, logger, false)
{
	m_puckTargetFetcher = new ColorDependentPuckTargetFetcherToHidePucks(m_field);
	State *initialState = new DrivePuckStateMachine::InitialState(robot, field, referee, logger, *m_puckTargetFetcher);
	m_puckTargetFetcherStateMachine = new StateMachine(initialState, robot, field, referee);
}

HideEnemyPucks::~HideEnemyPucks()
{
	delete m_puckTargetFetcherStateMachine;
	m_puckTargetFetcherStateMachine = 0;
	delete m_puckTargetFetcher;
	m_puckTargetFetcher = 0;
}

State* HideEnemyPucks::nextState()
{
	if(m_referee.gameOver() || m_referee.stopMovement())
		return new Pause(m_robot, m_field, m_referee, m_logger);
	else if(m_field.getNumberOfAchievedGoals() < 3 && m_robot.reachedTarget())
		return new AchieveGoals(m_robot, m_field, m_referee, m_logger);
	else if(m_field.getNumberOfHiddenPucks() >= 3 && m_field.getNumberOfAchievedGoals() >=3 && m_robot.reachedTarget())
		return new DriveToFinalPosition(m_robot, m_field, m_referee, m_logger);
	else
		return 0;
}

std::string HideEnemyPucks::getName()
{
	return "HideEnemyPucks: " + m_puckTargetFetcherStateMachine->getNameOfCurrentState();
}

void HideEnemyPucks::updateInternal()
{
	m_puckTargetFetcherStateMachine->update();
}

