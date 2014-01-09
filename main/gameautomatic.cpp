#include "main/gameautomatic.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/mainstatemachine/initialstate.h"
#include "layer/view/model.h"
#include "layer/view/controller.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/robot.h"
#include "common/console.h"
#include <iostream>

using namespace std;
using namespace RoboHockey;
using namespace RoboHockey::Common;
using namespace RoboHockey::Main;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;

GameAutomatic::GameAutomatic(int argc, char **argv) :
	Game(argc, argv),
	m_stateMachine(0),
	m_oldString(""),
	m_model(new Model()),
	m_controller(new Controller(*m_model))
{
	InitialState *initialState = new InitialState(getRobot(), getField(), getReferee());
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

	if(m_oldString != m_stateMachine->getNameOfCurrentState())
	{
		m_oldString = m_stateMachine->getNameOfCurrentState();
		cout << "current state: " << m_stateMachine->getNameOfCurrentState() << endl;
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

