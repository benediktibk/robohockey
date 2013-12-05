#include "main/gameautomatic.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/initialstate.h"
#include "common/console.h"

using namespace RoboHockey;
using namespace RoboHockey::Common;
using namespace RoboHockey::Main;
using namespace RoboHockey::Layer::Strategy;

GameAutomatic::GameAutomatic(int argc, char **argv) :
	Game(argc, argv),
	m_stateMachine(0)
{
	InitialState *initialState = new InitialState(getRobot(), getField(), getReferee());
	m_stateMachine = new StateMachine(initialState, getRobot(), getField(), getReferee());
}

GameAutomatic::~GameAutomatic()
{
	delete m_stateMachine;
	m_stateMachine = 0;
}

bool GameAutomatic::keepRunning() const
{
	char key = Console::getAsynchronousInput();
	return key != 'q';
}

void GameAutomatic::executeRobotControl()
{
	m_stateMachine->update();
}

