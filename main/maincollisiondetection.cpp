#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/dataanalysis/lidar.h"
#include "layer/hardware/robotimpl.h"
#include "common/watchimpl.h"
#include "common/loggerimpl.h"
#include <iostream>
#include <stdio.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;

	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(argv[1]);
	WatchImpl watch;
	LoggerImpl logger;
	DataAnalyserImpl dataAnalyser(hardwareRobot, watch, logger);
	const Lidar &lidar = dataAnalyser.getLidar();
	Sonar &sonar = dataAnalyser.getSonar();
	Hardware::Sonar &hardwareSonar = hardwareRobot->getSonar();
	char key = 0;

	cout << "press q to quit and any key to get next result" << endl;

	while(key != 'q')
	{
		dataAnalyser.updateSensorData();
		bool sonarValue = sonar.isObstacleDirectInFront(0.5);
		bool lidarValue = lidar.isObstacleInFront(0.5);

		if (sonarValue)
			cout << "obstacle is in front of sonar" << endl;
		else
			cout << "no obstacle in front of sonar" << endl;

		if (lidarValue)
			cout << "obstacle is in front of lidar" << endl;
		else
			cout << "no obstacle in front of lidar" << endl;

		cout << "sonar, left front: " << hardwareSonar.getDistanceForSensor(3) << endl;
		cout << "sonar, right front: " << hardwareSonar.getDistanceForSensor(4) << endl;

		key = getchar();
	}

	return 0;
}
