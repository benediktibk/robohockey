#include "main/gameautomatic.h"

using namespace RoboHockey::Main;

int main(int argc, char **argv)
{
	GameAutomatic game(argc, argv);
	game.execute();
	return 0;
}
