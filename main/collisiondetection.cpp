#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/dataanalysis/lidar.h"
#include "layer/hardware/robotimpl.h"
#include <iostream>
#include <stdio.h>

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;

	DataAnalyserImpl dataAnalyser(new Hardware::RobotImpl(argv[1]));
	const Lidar &lidar = dataAnalyser.getLidar();
	Sonar &sonar = dataAnalyser.getSonar();
	char key = 0;

	cout << "press q to quit and any key to get next result" << endl;

	while(key != 'q')
	{
		dataAnalyser.updateSensorData();
		bool sonarValue = sonar.isObstacleDirectInFront();
		bool lidarValue = lidar.isObstacleInFront();

		if (sonarValue)
			cout << "obstacle is in front of sonar" << endl;
		else
			cout << "no obstacle in front of sonar" << endl;

		if (lidarValue)
			cout << "obstacle is in front of lidar" << endl;
		else
			cout << "no obstacle in front of lidar" << endl;

		key = getchar();
	}

	return 0;
}
