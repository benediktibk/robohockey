#include "main/gameremotecontrol.h"
#include <QtGui/QApplication>

using namespace RoboHockey::Main;

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	GameRemoteControl game(argc, argv);
	return application.exec();
}
