#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/hardware/robotimpl.h"
#include <iostream>
#include <stdio.h>

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

int main(int, char**)
{
	DataAnalyserImpl dataAnalyser(new Hardware::RobotImpl("localhost"));
	Sonar &sonar = dataAnalyser.getSonar();
	char key = 0;

	cout << "press q to quit and any key to get next result" << endl;

	while(key != 'q')
	{
		dataAnalyser.updateSensorData();
		bool value = sonar.isObstacleDirectInFront(0.3);

		if (value)
			cout << "obstacle is in front" << endl;
		else
			cout << "no obstacle in front" << endl;

		key = getchar();
	}

	return 0;
}
