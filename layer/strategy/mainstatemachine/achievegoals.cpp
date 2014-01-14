#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/common/colordependentpucktargetfetchertoachivegoals.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

AchieveGoals::AchieveGoals(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger) :
	State(robot, field, referee, logger, false)
{
	m_puckTargetFetcher = new ColorDependentPuckTargetFetcherToAchiveGoals(m_field);
	State *initialState = new DrivePuckStateMachine::InitialState(robot, field, referee, logger, *m_puckTargetFetcher);
	m_puckTargetFetcherStateMachine = new StateMachine(initialState, robot, field, referee);
}

AchieveGoals::~AchieveGoals()
{
	delete m_puckTargetFetcherStateMachine;
	m_puckTargetFetcherStateMachine = 0;
	delete m_puckTargetFetcher;
	m_puckTargetFetcher = 0;
}

State* AchieveGoals::nextState()
{
	if(m_referee.stopMovement() || m_referee.gameOver())
		return new Pause(m_robot, m_field, m_referee, m_logger);
	else if(m_field.getNumberOfAchievedGoals() < 3)
		return 0;
	else
		return new HideEnemyPucks(m_robot, m_field, m_referee, m_logger);
}

std::string AchieveGoals::getName()
{
	return "AchiveGoals: " + m_puckTargetFetcherStateMachine->getNameOfCurrentState();
}

void AchieveGoals::updateInternal()
{
	m_puckTargetFetcherStateMachine->update();
}
