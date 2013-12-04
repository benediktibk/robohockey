#include "common/console.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace RoboHockey::Common;

char Console::getAsynchronousInput()
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

Console::Console()
{ }

