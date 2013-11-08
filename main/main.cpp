#include "layer/hardware/robotimpl.h"
#include <iostream>

using namespace RoboHockey;
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

	Layer::Hardware::Robot *robot = new Layer::Hardware::RobotImpl(playerServer);
	delete robot;
	return 0;
}
