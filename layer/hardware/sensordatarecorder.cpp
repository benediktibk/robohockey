#include "layer/hardware/sensordatarecorder.h"
#include "layer/hardware/robot.h"
#include "layer/hardware/lidar.h"
#include "layer/hardware/sonar.h"
#include "layer/hardware/odometry.h"
#include "layer/hardware/engine.h"
#include "layer/hardware/camera.h"
#include <boost/filesystem.hpp>
#include <assert.h>
#include <sstream>
#include <fstream>

using namespace std;
using namespace boost;
using namespace RoboHockey::Layer::Hardware;

SensorDataRecorder::SensorDataRecorder(const Robot &robot, const string &path) :
	m_robot(robot),
	m_path(path),
	m_roundCount(0)
{
	assert(!filesystem::exists(m_path));
	filesystem::create_directory(m_path);
}

void SensorDataRecorder::recordCurrentValues()
{
	const Lidar &lidar = m_robot.getLidar();
	const Camera &camera = m_robot.getCamera();
	const Sonar &sonar = m_robot.getSonar();
	const Odometry &odometry = m_robot.getOdometry();
	const Engine &engine = m_robot.getEngine();
	stringstream lidarFileName;
	stringstream cameraFileName;
	stringstream sonarFileName;
	stringstream odometryFileName;
	stringstream engineFileName;

	lidarFileName << m_path << "/lidar_" << m_roundCount << ".txt";
	cameraFileName << m_path << "/camera_" << m_roundCount << ".png";
	sonarFileName << m_path << "/sonar_" << m_roundCount << ".txt";
	odometryFileName << m_path << "/odometry_" << m_roundCount << ".txt";
	engineFileName << m_path << "/engine_" << m_roundCount << ".txt";

	if (!engine.isMoving() && camera.isValid())
		camera.writeDataToFile(cameraFileName.str());

	lidar.writeDataToFile(lidarFileName.str());
	sonar.writeDataToFile(sonarFileName.str());
	odometry.writeDataToFile(odometryFileName.str());
	engine.writeDataToFile(engineFileName.str());

	fstream roundCount("roundcount.txt", ios::out | ios::trunc);
	roundCount << m_roundCount;
	roundCount.close();
	++m_roundCount;
}
