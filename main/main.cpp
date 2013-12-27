#include "main/gameautomatic.h"
#include <QtGui/QApplication>

using namespace RoboHockey::Main;

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	GameAutomatic game(argc, argv);
	return application.exec();
}
