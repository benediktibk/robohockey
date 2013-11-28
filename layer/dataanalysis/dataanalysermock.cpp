#include "layer/dataanalysis/dataanalysermock.h"

using namespace RoboHockey::Layer::DataAnalysis;

DataAnalyserMock::DataAnalyserMock() :
	m_callsToUpdateSensorData(0),
	m_callsToUpdateActuators(0)
{ }

Sonar &DataAnalyserMock::getSonar()
{
	return m_sonar;
}

const Lidar &DataAnalyserMock::getLidar() const
{
	return m_lidar;
}

Camera &DataAnalyserMock::getCamera()
{
	return m_camera;
}

Odometry &DataAnalyserMock::getOdometry()
{
	return m_odometry;
}

Engine &DataAnalyserMock::getEngine()
{
	return m_engine;
}

void DataAnalyserMock::updateSensorData()
{
	++m_callsToUpdateSensorData;
}

void DataAnalyserMock::updateActuators()
{
	++m_callsToUpdateActuators;
}

EngineMock &DataAnalyserMock::getEngineMock()
{
	return m_engine;
}

SonarMock &DataAnalyserMock::getSonarMock()
{
	return m_sonar;
}

OdometryMock &DataAnalyserMock::getOdometryMock()
{
	return m_odometry;
}

LidarMock &DataAnalyserMock::getLidarMock()
{
	return m_lidar;
}

unsigned int DataAnalyserMock::getCallsToUpdateSensorData() const
{
	return m_callsToUpdateSensorData;
}

unsigned int DataAnalyserMock::getCallsToUpdateActuators() const
{
	return m_callsToUpdateActuators;
}
