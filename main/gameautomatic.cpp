#include "main/gameautomatic.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/mainstatemachine/initialstate.h"
#include "common/console.h"
#include <iostream>

using namespace std;
using namespace RoboHockey;
using namespace RoboHockey::Common;
using namespace RoboHockey::Main;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;

GameAutomatic::GameAutomatic(int argc, char **argv) :
	Game(argc, argv),
	m_stateMachine(0),
	m_oldString("")
{
	InitialState *initialState = new InitialState(getRobot(), getField(), getReferee());
	m_stateMachine = new StateMachine(initialState, getRobot(), getField(), getReferee());

	cout << "starting the robot" << endl;
	cout << "program can be closed with 'q'" << endl;
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
	if(m_oldString != m_stateMachine->getNameOfCurrentState())
	{
		m_oldString = m_stateMachine->getNameOfCurrentState();
		cout << "Current State: " << m_stateMachine->getNameOfCurrentState() << endl;
	}
}

