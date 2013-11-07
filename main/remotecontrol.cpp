#include <QtGui/QApplication>
#include "layer/view/viewer.h"
#include "layer/view/model.h"
#include "layer/view/robotdriver.h"
#include "layer/view/robotdriverloop.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::View;

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	Viewer view;
	Model model;
	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl();
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::RobotImpl autonomousRobot(dataAnalyser);
	RobotDriver robotDriver(autonomousRobot, model);
	RobotDriverLoop loop(robotDriver);
	view.show();
	return application.exec();
}
