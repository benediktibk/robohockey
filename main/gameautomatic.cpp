#include "main/gameautomatic.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/mainstatemachine/initialstate.h"
#include "layer/view/model.h"
#include "layer/view/controller.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/robot.h"
#include "common/console.h"
#include "common/logger.h"
#include <iostream>

using namespace std;
using namespace RoboHockey;
using namespace RoboHockey::Common;
using namespace RoboHockey::Main;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

GameAutomatic::GameAutomatic(int argc, char **argv) :
	Game(argc, argv),
	m_stateMachine(0),
	m_stateString(""),
	m_model(new Model()),
	m_controller(new Controller(*m_model))
{
	InitialState *initialState = new InitialState(getRobot(), getField(), getReferee(), getLogger());
	m_stateMachine = new StateMachine(initialState, getRobot(), getField(), getReferee());

	cout << "starting the robot" << endl;
	cout << "program can be closed with 'q'" << endl;

	if(guiEnabled())
		m_controller->show();
}

GameAutomatic::~GameAutomatic()
{
	delete m_stateMachine;
	m_stateMachine = 0;
	delete m_controller;
	m_controller = 0;
	delete m_model;
	m_model = 0;
}

bool GameAutomatic::keepRunning() const
{
	char key = Console::getAsynchronousInput();
	return key != 'q';
}

void GameAutomatic::executeRobotControl()
{
	m_stateMachine->update();
	setLogMessagesEnabled(m_stateMachine->allowLogMessages());
	Robot &robot = getRobot();
	string stateString = m_stateMachine->getNameOfCurrentState();
	string robotString = robot.getCurrentState();
	Logger &logger = getLogger();

	if(m_stateString != stateString)
	{
		m_stateString = stateString;
		logger.logToConsoleAndGlobalLogFile("current state: " + m_stateString);
	}

	if (m_robotString != robotString)
	{
		m_robotString = robotString;
		logger.logToConsoleAndGlobalLogFile("robot does: " + m_robotString);
	}

	if (guiEnabled() && logMessagesEnabled())
	{
		Layer::Autonomous::Robot &robot = getRobot();
		Layer::Autonomous::Field &field = getField();

		m_model->setData(
					field.getAllFieldObjects(), robot.getAllRoutePoints(), robot.stuckAtObstacle(),
					robot.reachedTarget(), robot.getCurrentPosition(),
					Point::zero(), robot.isMoving(), robot.cantReachTarget(),
					robot.isPuckCollected(), robot.isPuckCollectable(), false,
					Point::zero(), robot.isRotating());
	}
}

