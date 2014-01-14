#include "layer/hardware/robotmock.h"

using namespace RoboHockey::Layer::Hardware;

RobotMock::RobotMock() :
	m_callsToGetSonar(0),
	m_callsToGetLidar(0),
	m_callsToGetCamera(0),
	m_callsToGetOdometry(0),
	m_callsToGetEngine(0),
	m_callsToGetSensorData(0)
{ }

Sonar &RobotMock::getSonar()
{
	++m_callsToGetSonar;
	return m_sonar;
}

Lidar &RobotMock::getLidar()
{
	++m_callsToGetLidar;
	return m_lidar;
}

Camera &RobotMock::getCamera()
{
	++m_callsToGetCamera;
	return m_camera;
}

Odometry &RobotMock::getOdometry()
{
	++m_callsToGetOdometry;
	return m_odometry;
}

Engine &RobotMock::getEngine()
{
	++m_callsToGetEngine;
	return m_engine;
}

const Sonar &RobotMock::getSonar() const
{
	return m_sonar;
}

const Lidar &RobotMock::getLidar() const
{
	return m_lidar;
}

const Camera &RobotMock::getCamera() const
{
	return m_camera;
}

const Odometry &RobotMock::getOdometry() const
{
	return m_odometry;
}

const Engine &RobotMock::getEngine() const
{
	return m_engine;
}

void RobotMock::updateSensorData()
{
	++m_callsToGetSensorData;
}

unsigned int RobotMock::getCallsToGetSonar() const
{
	return m_callsToGetSonar;
}

unsigned int RobotMock::getCallsToGetLidar() const
{
	return m_callsToGetLidar;
}

unsigned int RobotMock::getCallsToGetCamera() const
{
	return m_callsToGetCamera;
}

unsigned int RobotMock::getCallsToGetOdometry() const
{
	return m_callsToGetOdometry;
}

unsigned int RobotMock::getCallsToGetEngine() const
{
	return m_callsToGetEngine;
}

unsigned int RobotMock::getCallsToGetSensorData() const
{
	return m_callsToGetSensorData;
}

EngineMock &RobotMock::getEngineMock()
{
	return m_engine;
}

OdometryMock &RobotMock::getOdometryMock()
{
	return m_odometry;
}

LidarMock &RobotMock::getLidarMock()
{
	return m_lidar;
}

SonarMock &RobotMock::getSonarMock()
{
	return m_sonar;
}

CameraMock &RobotMock::getCameraMock()
{
	return m_camera;
}
