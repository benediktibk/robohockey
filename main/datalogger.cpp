#include "layer/hardware/robotimpl.h"
#include "layer/hardware/sonar.h"
#include "layer/hardware/lidar.h"
#include "layer/hardware/camera.h"
#include "layer/hardware/odometry.h"
#include "common/point.h"
#include "common/robotposition.h"
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <iostream>

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;
using namespace std;

int main(int argc, char **argv)
{
	string playerServer;
	if (argc == 2)
		playerServer = argv[1];
	else
	{
		cout << "no player server selected, using localhost" << endl;
		playerServer = "localhost";
	}

	RobotImpl robot(playerServer);
	Sonar &sonar = robot.getSonar();
	Lidar &lidar = robot.getLidar();
	Camera &camera = robot.getCamera();
	Odometry &odometry = robot.getOdometry();
	fstream fileSonar("sonar.txt", ios_base::out | ios_base::trunc);
	fstream fileLidar("lidar.txt", ios_base::out | ios_base::trunc);
	fstream fileOdometry("odometry.txt", ios_base::out | ios_base::trunc);

	cout << "updating the current sensor data" << endl;
	robot.updateSensorData();

	cout << "writing data for the sonar to sonar.txt" << endl;
	for (unsigned int i = sonar.getMinimumSensorNumber(); i <= sonar.getMaximumSensorNumber(); ++i)
		fileSonar << i << ": " << sonar.getDistanceForSensor(i) << endl;

	cout << "writing data for the lidar to lidar.txt" << endl;
	for (unsigned int i = lidar.getMinimumSensorNumber(); i <= lidar.getMaximumSensorNumber(); ++i)
		fileLidar << i << ": " << lidar.getDistance(i) << endl;

	cout << "writing data for the odometry to odometry.txt" << endl;
	RobotPosition currentPosition = odometry.getCurrentPosition();
	fileOdometry << "(x, y, alpha): " << currentPosition << endl;

	if (camera.isValid())
	{
		cout << "writing data for the camera to camera.bmp" << endl;
		cv::Mat frame = camera.getFrame();
		imwrite("camera.bmp", frame);
	}
	else
		cout << "couldn't open the camera" << endl;

	return 0;
}
