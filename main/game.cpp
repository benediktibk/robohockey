#include "main/game.h"
#include "common/watch.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/routerimpl.h"
#include "layer/strategy/refereeimpl.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace RoboHockey;
using namespace RoboHockey::Common;
using namespace RoboHockey::Main;
using namespace RoboHockey::Layer;

Game::Game(int argc, char **argv) :
	m_robot(0),
	m_field(0),
	m_referee(0),
	m_watch(new Common::Watch()),
	m_timer(new QTimer())
{
	string playerServer;
	if (argc == 2)
		playerServer = argv[1];
	else
	{
		cout << "no player server selected, using localhost" << endl;
		playerServer = "localhost";
	}

	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(playerServer);
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::Router *router = new Autonomous::RouterImpl(0.38);
	m_robot = new Autonomous::RobotImpl(dataAnalyser, router);
	m_field = new Autonomous::FieldImpl(
				dataAnalyser->getOdometry(), dataAnalyser->getLidar(),
				dataAnalyser->getCamera(), *m_robot);
	m_referee = new Strategy::RefereeImpl();

	connect(m_timer, SIGNAL(timeout()), this, SLOT(execute()));

	m_watch->getTimeAndRestart();
	m_timer->start(0);
}

Game::~Game()
{
	delete m_watch;
	m_watch = 0;
	delete m_field;
	m_field = 0;
	delete m_robot;
	m_robot = 0;
	delete m_referee;
	m_referee = 0;
}

void Game::execute()
{
	Watch watch;

	m_robot->updateSensorData();
	double timeForSensorUpdate = watch.getTimeAndRestart();
	m_field->update();
	double timeForFieldUpdate = watch.getTimeAndRestart();
	executeRobotControl();
	double timeForLogic = watch.getTimeAndRestart();
	m_robot->updateActuators(*m_field);
	double timeForActuatorUpdate = watch.getTimeAndRestart();

	double timeDifference = m_watch->getTimeAndRestart();
	if (timeDifference > 0.11 && m_robot->isMoving())
	{
		printTimeInMs("loop time is too high", timeDifference);
		printTimeInMs("time spent on sensor updates", timeForSensorUpdate);
		printTimeInMs("time spent on field update", timeForFieldUpdate);
		printTimeInMs("time spent on logic", timeForLogic);
		printTimeInMs("time spent on actuator updates", timeForActuatorUpdate);
	}

	if (keepRunning())
		m_timer->start(0);
	else
		QCoreApplication::quit();
}

Autonomous::Robot &Game::getRobot()
{
	return *m_robot;
}

Autonomous::Field &Game::getField()
{
	return *m_field;
}

Strategy::Referee &Game::getReferee()
{
	return *m_referee;
}

void Game::printTimeInMs(const string &message, double time) const
{
	cout << setprecision(1) << fixed << message << ": " << time*1000 << " ms" << endl;
}

