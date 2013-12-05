#include "main/gameremotecontrol.h"
#include <iostream>

using namespace RoboHockey::Main;
using namespace std;

int main(int argc, char **argv)
{
	GameRemoteControl game(argc, argv);
	bool running = true;

	cout << "starting the remote control" << endl;

	while(running)
	{
		game.execute();
		running = game.keepRunning();
	}
}
