#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include "layer/dataanalysis/sonar.h"
#include <iostream>

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Layer;
using namespace std;

int main(int, char**)
{
	DataAnalyserImpl dataAnalyser(new Hardware::RobotImpl("192.168.1.102"));
	Sonar &sonar = dataAnalyser.getSonar();
	char key = 0;

	cout << "press q to quit and any key to get next result" << endl;

	while(key != 'q')
	{
		dataAnalyser.updateSensorData();
		bool value = sonar.isObstacleDirectInFront();

		if (value)
			cout << "obstacle is in front" << endl;
		else
			cout << "no obstacle in front" << endl;

		cin >> key;
	}

	return 0;
}
