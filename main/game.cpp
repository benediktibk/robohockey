#include "main/game.h"
#include "common/watch.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/strategy/refereeimpl.h"
#include <QtGui/QApplication>
#include <QStringList>
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
	m_application(new QApplication(argc, argv))
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
	m_robot = new Autonomous::RobotImpl(dataAnalyser);
	m_field = new Autonomous::FieldImpl(
				dataAnalyser->getOdometry(), dataAnalyser->getLidar(),
				dataAnalyser->getCamera(), *m_robot);
	m_referee = new Strategy::RefereeImpl();
	m_application->arguments();
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
	delete m_application;
	m_application = 0;
}

void Game::execute()
{
	Watch watch;
	m_watch->getTimeAndRestart();

	while (keepRunning())
	{
		watch.getTimeAndRestart();
		m_application->processEvents();
		m_application->sendPostedEvents();
		double timeForEventProcessing = watch.getTimeAndRestart();
		m_robot->updateSensorData();
		double timeForFieldUpdate = watch.getTimeAndRestart();
		m_field->update();
		double timeForSensorUpdate = watch.getTimeAndRestart();
		executeRobotControl();
		double timeForLogic = watch.getTimeAndRestart();
		m_robot->updateActuators(*m_field);
		double timeForActuatorUpdate = watch.getTimeAndRestart();

		double timeDifference = m_watch->getTimeAndRestart();
		if (timeDifference > 0.11 && m_robot->isMoving())
		{
			printTimeInMs("loop time is too high", timeDifference);
			printTimeInMs("time spent on event processing", timeForEventProcessing);
			printTimeInMs("time spent on sensor updates", timeForSensorUpdate);
			printTimeInMs("time spent on field update", timeForFieldUpdate);
			printTimeInMs("time spent on logic", timeForLogic);
			printTimeInMs("time spent on actuator updates", timeForActuatorUpdate);
		}
	}
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
	cout << setprecision(3) << fixed << message << ": " << time/1000 << " ms" << endl;
}

