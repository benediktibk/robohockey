#include "main/gameautomatic.h"
#include "common/console.h"
#include <iostream>

using namespace std;
using namespace RoboHockey::Main;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;

int main(int argc, char **argv)
{
	GameAutomatic game(argc, argv);
	bool running = true;

	cout << "program can be closed with 'q'" << endl;

	while(running)
	{
		game.execute();

		char key = Console::getAsynchronousInput();
		running = key != 'q';
	}

	return 0;
}
