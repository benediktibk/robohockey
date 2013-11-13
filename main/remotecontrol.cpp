#include <QtGui/QApplication>
#include "layer/view/viewer.h"
#include "layer/view/model.h"
#include "layer/view/robotdriver.h"
#include "layer/view/robotdriverloop.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include <iostream>
#include "layer/view/viewer.h"
#include "layer/view/graph.h"

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

    QGraph qshow;
    //Viewer view;
	Model model;
	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(playerServer);
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::RobotImpl autonomousRobot(dataAnalyser);
	RobotDriver robotDriver(autonomousRobot, model);
	RobotDriverLoop loop(robotDriver);

//	vector<RoboHockey::Common::Point> targets;
//	targets.push_back(RoboHockey::Common::Point(-4, 0));
//	targets.push_back(RoboHockey::Common::Point(0, 3));
//	model.setData(targets);
	//autonomousRobot.turnTo(RoboHockey::Common::Point(-1, 0));

    //view.show();
    qshow.show();
	return application.exec();
}
