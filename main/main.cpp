#include "layer/hardware/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/initialstate.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/strategy/refereeimpl.h"
#include "common/watch.h"
#include "common/console.h"
#include <iostream>
#include <boost/scoped_ptr.hpp>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace std;
using namespace boost;

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

	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(playerServer);
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::RobotImpl autonomousRobot(dataAnalyser);
	Autonomous::FieldImpl autonomousField(
				dataAnalyser->getOdometry(), dataAnalyser->getLidar(),
				dataAnalyser->getCamera(), autonomousRobot);
	Strategy::RefereeImpl referee;
	Strategy::StateMachine stateMachine(
                new Strategy::InitialState(autonomousRobot, autonomousField, referee),
				autonomousRobot, autonomousField, referee);
	bool running = true;
	const double maximumLoopTime = 0.1;

	cout << "program can be closed with 'q'" << endl;

	while(running)
	{
		autonomousRobot.updateSensorData();
		autonomousField.update();
		stateMachine.update();
		autonomousRobot.updateActuators(autonomousField);

		char key = Console::getAsynchronousInput();

		if (key == 'q')
			running = false;
		else
			running = true;

		double timeDifference = Watch::getTimeAndRestart();

		if (timeDifference > maximumLoopTime)
			cout << "loop time is too high: " << timeDifference*1000 << " ms" << endl;
	}

	return 0;
}
