#include "layer/hardware/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/initialstate.h"
#include <iostream>

using namespace RoboHockey::Layer;
using namespace std;

int main(int argc, char **argv)
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
	cout << "program can be closed with 'q'" << endl;

	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(playerServer);
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::Robot *autonomousRobot = new Autonomous::RobotImpl(dataAnalyser);
	Strategy::StateMachine stateMachine(new Strategy::InitialState(*autonomousRobot), autonomousRobot);
	bool running = true;

	while(running)
	{
		stateMachine.update();
		//! @todo check keyboard asynchronous for q
		running = true;
	}

	return 0;
}
