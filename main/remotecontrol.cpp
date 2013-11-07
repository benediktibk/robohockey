#include <QtGui/QApplication>
#include "layer/view/viewer.h"
#include "layer/view/model.h"
#include "layer/view/robotdriver.h"
#include "layer/view/robotdriverloop.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include <iostream>

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::View;
using namespace std;

int main(int argc, char **argv)
{
	cout << "starting the remote control" << endl;

	QApplication application(argc, argv);
	Viewer view;
	Model model;
	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl();
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::RobotImpl autonomousRobot(dataAnalyser);
	RobotDriver robotDriver(autonomousRobot, model);
	RobotDriverLoop loop(robotDriver);

	// uncomment this to see some movement
//	std::vector<RoboHockey::Common::Point> targets;
//	targets.push_back(RoboHockey::Common::Point(-1, 0));
//	targets.push_back(RoboHockey::Common::Point(0, 4));
//	targets.push_back(RoboHockey::Common::Point(1, 4));
//	targets.push_back(RoboHockey::Common::Point(0, 4));
//	model.setData(targets);

	view.show();
	return application.exec();
}
