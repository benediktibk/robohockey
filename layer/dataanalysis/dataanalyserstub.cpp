#include "layer/dataanalysis/dataanalyserstub.h"

using namespace RoboHockey::Layer::DataAnalysis;

const Sonar &DataAnalyserStub::getSonar() const
{
	return m_sonar;
}

const Lidar &DataAnalyserStub::getLidar() const
{
	return m_lidar;
}

const Camera &DataAnalyserStub::getCamera() const
{
	return m_camera;
}

Odometry &DataAnalyserStub::getOdometry()
{
	return m_odometry;
}

Engine &DataAnalyserStub::getEngine()
{
	return m_engine;
}

void DataAnalyserStub::updateSensorData()
{ }

void DataAnalyserStub::updateActuators()
{ }
