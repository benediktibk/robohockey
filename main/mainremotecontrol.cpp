#include "main/gameremotecontrol.h"

using namespace RoboHockey::Main;

int main(int argc, char **argv)
{
	GameRemoteControl game(argc, argv);
	game.execute();
	return 0;
}
