#include "main/game.h"
#include "common/watch.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/routerimpl.h"
#include "layer/strategy/mainstatemachine/refereeimpl.h"
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
	m_referee = new Strategy::MainStateMachine::RefereeImpl();

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

	/*!
	 * Unfortunately disabling the engine is very slow, this seems
	 * to be a blocking call. If we then decide to stop and disable
	 * the engine we would get in this iteration a very loop time.
	 * After this step the robot would say he is not moving anymore,
	 * but still the loop time is very high. Therefore we check if
	 * the robot is moving previously to avoid this problem.
	 */
	bool isMovingPreviously = m_robot->isMoving();
	m_robot->updateSensorData();
	double timeForSensorUpdate = watch.getTimeAndRestart();
	m_field->update();
	double timeForFieldUpdate = watch.getTimeAndRestart();
	executeRobotControl();
	double timeForLogic = watch.getTimeAndRestart();
	m_robot->updateActuators(*m_field);
	double timeForActuatorUpdate = watch.getTimeAndRestart();
	bool isMovingAfterwards = m_robot->isMoving();

	double timeDifference = m_watch->getTimeAndRestart();
	double timeForEventProcessing =
			timeDifference -
			(timeForActuatorUpdate + timeForFieldUpdate + timeForLogic + timeForSensorUpdate);
	if (timeDifference > 0.11 && isMovingPreviously && isMovingAfterwards)
	{
		printTimeInMs("loop time is too high", timeDifference);
		printTimeInMs("time spent on sensor updates", timeForSensorUpdate);
		printTimeInMs("time spent on field update", timeForFieldUpdate);
		printTimeInMs("time spent on logic", timeForLogic);
		printTimeInMs("time spent on actuator updates", timeForActuatorUpdate);
		printTimeInMs("time spent on event processing", timeForEventProcessing);
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

Strategy::MainStateMachine::Referee &Game::getReferee()
{
	return *m_referee;
}

void Game::printTimeInMs(const string &message, double time) const
{
	cout << setprecision(1) << fixed << message << ": " << time*1000 << " ms" << endl;
}

