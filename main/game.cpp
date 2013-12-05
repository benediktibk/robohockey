#include "main/game.h"
#include "common/watch.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/strategy/refereeimpl.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace RoboHockey;
using namespace RoboHockey::Main;
using namespace RoboHockey::Layer;

Game::Game(int argc, char **argv) :
	m_robot(0),
	m_field(0),
	m_referee(0),
	m_watch(new Common::Watch())
{
	string playerServer;
	if (argc == 2)
		playerServer = argv[1];
	else
	{
		cout << "no player server selected, using localhost" << endl;
		playerServer = "localhost";
	}

	cout << "starting the robot" << endl;

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
}

void Game::execute()
{
	m_robot->updateSensorData();
	m_field->update();
	executeRobotControl();
	m_robot->updateActuators(*m_field);

	double timeDifference = m_watch->getTimeAndRestart();
	cout << setprecision(3) << fixed << "loop time: " << timeDifference*1000 << " ms" << endl;
	if (timeDifference > 0.11)
		cout << setprecision(3) << fixed << "loop time is too high!" << endl;
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

