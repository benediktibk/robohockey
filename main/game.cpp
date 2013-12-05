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
	m_application(new QApplication(argc, argv)),
	m_eventLoop(new QEventLoop(0))
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
	delete m_eventLoop;
	m_eventLoop = 0;
}

void Game::execute()
{
	Watch watch;

	while (keepRunning())
	{
		watch.getTimeAndRestart();
		m_eventLoop->processEvents();
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
		cout << setprecision(3) << fixed << "loop time: " << timeDifference*1000 << " ms" << endl;
		if (timeDifference > 0.11)
		{
			cout << setprecision(3) << fixed << "loop time is too high!" << endl;
			cout << setprecision(3) << fixed << "time spent on event processing: " << timeForEventProcessing << endl;
			cout << setprecision(3) << fixed << "time spent on sensor updates: " << timeForSensorUpdate << endl;
			cout << setprecision(3) << fixed << "time spent on field update: " << timeForFieldUpdate << endl;
			cout << setprecision(3) << fixed << "time spent on logic: " << timeForLogic << endl;
			cout << setprecision(3) << fixed << "time spent on actuator updates: " << timeForActuatorUpdate << endl;
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

