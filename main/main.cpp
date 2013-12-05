#include "main/gameautomatic.h"
#include <QtCore/QCoreApplication>

using namespace RoboHockey::Main;

int main(int argc, char **argv)
{
	QCoreApplication application(argc, argv);
	GameAutomatic game(argc, argv);
	return application.exec();
}
