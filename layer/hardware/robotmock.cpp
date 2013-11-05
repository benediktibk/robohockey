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
	return RobotStub::getSonar();
}

Lidar &RobotMock::getLidar()
{
	++m_callsToGetLidar;
	return RobotStub::getLidar();
}

Camera &RobotMock::getCamera()
{
	++m_callsToGetCamera;
	return RobotStub::getCamera();
}

Odometry &RobotMock::getOdometry()
{
	++m_callsToGetOdometry;
	return RobotStub::getOdometry();
}

Engine &RobotMock::getEngine()
{
	++m_callsToGetEngine;
	return RobotStub::getEngine();
}

void RobotMock::updateSensorData()
{
	++m_callsToGetSensorData;
	RobotStub::updateSensorData();
}


bool RobotMock::isValid() const
{
	return true;
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
