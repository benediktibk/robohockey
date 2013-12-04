#include "layer/hardware/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/strategy/statemachine.h"
#include "layer/strategy/initialstate.h"
#include "common/watch.h"
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <boost/scoped_ptr.hpp>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace std;
using namespace boost;

char kbhit(void)
{
  struct termios oldt, newt;
  char key;
  int oldf;

  // just copied from stackoverflow, got no idea what it actually does - Benedikt
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  key = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(key != EOF)
  {
	ungetc(key, stdin);
	return key;
  }

  return 0;
}

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

	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(playerServer);
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	scoped_ptr<Autonomous::Robot> autonomousRobot(new Autonomous::RobotImpl(dataAnalyser));
	scoped_ptr<Autonomous::FieldImpl> field(new Autonomous::FieldImpl(
												dataAnalyser->getOdometry(),
												dataAnalyser->getLidar(),
												dataAnalyser->getCamera(),
												*autonomousRobot));
	Strategy::StateMachine stateMachine(new Strategy::InitialState(*autonomousRobot), *autonomousRobot, *field);
	bool running = true;
	double lastTime = watch.getTime();
	const double maximumLoopTime = 0.1;

	cout << "program can be closed with 'q'" << endl;

	while(running)
	{
		stateMachine.update();
		char key = kbhit();

		if (key == 'q')
			running = false;
		else
			running = true;

		double currentTime = watch.getTime();
		double timeDifference = currentTime - lastTime;
		lastTime = currentTime;

		if (timeDifference > maximumLoopTime)
			cout << "loop time is too high: " << timeDifference*1000 << " ms" << endl;
	}

	return 0;
}
