#include "layer/view/model.h"
#include "layer/view/robotdriver.h"
#include "layer/view/robotdriverloop.h"
#include "layer/view/controller.h"
#include "layer/view/graph.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include <QtGui/QApplication>
#include <iostream>

using namespace RoboHockey;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::View;
using namespace std;

int main(int argc, char **argv)
{
	cout << "starting the remote control" << endl;

	QApplication application(argc, argv);
	QStringList arguments = application.arguments();
	string playerServer;

	if (arguments.size() == 2)
		playerServer = arguments[1].toStdString();
	else
	{
		cout << "no server selected, using localhost" << endl;
		playerServer = "localhost";
	}

	Model model;
    //Graph graph(model);
	Controller controller(model);
	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(playerServer);
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::RobotImpl autonomousRobot(dataAnalyser);
	RobotDriver robotDriver(autonomousRobot, model);
	RobotDriverLoop loop(robotDriver);

    controller.show();
    //graph.show();
	return application.exec();
}
