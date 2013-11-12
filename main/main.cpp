#include "layer/hardware/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/initialstate.h"
#include "common/watch.h"
#include <iostream>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace std;

int main(int argc, char **argv)
{
	Watch watch;
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
	double lastTime = watch.getTime();
	const double maximumLoopTime = 0.1;

	while(running)
	{
		stateMachine.update();
		//! @todo check keyboard asynchronous for q
		running = true;
		double currentTime = watch.getTime();
		double timeDifference = currentTime - lastTime;
		lastTime = currentTime;

		if (timeDifference > maximumLoopTime)
			cout << "loop time is too high: " << timeDifference*1000 << " ms" << endl;
	}

	return 0;
}
