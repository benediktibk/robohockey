#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robot.h"
#include "layer/dataanalysis/cameraimpl.h"
#include "layer/dataanalysis/engineimpl.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/dataanalysis/odometryimpl.h"
#include "layer/dataanalysis/sonarimpl.h"
#include <assert.h>

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

DataAnalyserImpl::DataAnalyserImpl(Hardware::Robot *robot) :
	m_robot(robot),
	m_minimumDistanceToObstacle(0.45),
	m_sonar(new SonarImpl(m_robot->getSonar(), m_minimumDistanceToObstacle)),
	m_lidar(new LidarImpl(m_robot->getLidar(), m_minimumDistanceToObstacle)),
	m_camera(new CameraImpl(m_robot->getCamera())),
	m_odometry(new OdometryImpl(m_robot->getOdometry())),
	m_engine(new EngineImpl(m_robot->getEngine(), m_robot->getOdometry()))
{
	assert(m_robot != 0);
}

DataAnalyserImpl::~DataAnalyserImpl()
{
	delete m_sonar;
	m_sonar = 0;
	delete m_lidar;
	m_lidar = 0;
	delete m_camera;
	m_camera = 0;
	delete m_odometry;
	m_odometry = 0;
	delete m_engine;
	m_engine = 0;
	delete m_robot;
	m_robot = 0;
}

Sonar &DataAnalyserImpl::getSonar()
{
	return *m_sonar;
}

const Lidar &DataAnalyserImpl::getLidar() const
{
	return *m_lidar;
}

const Camera &DataAnalyserImpl::getCamera() const
{
	return *m_camera;
}

Odometry &DataAnalyserImpl::getOdometry()
{
	return *m_odometry;
}

Engine &DataAnalyserImpl::getEngine()
{
	return *m_engine;
}

void DataAnalyserImpl::updateSensorData()
{
	m_robot->updateSensorData();
}

void DataAnalyserImpl::updateActuators()
{
	m_engine->updateSpeedAndRotation();
}

DataAnalyserImpl::DataAnalyserImpl(const DataAnalyserImpl &) :
	m_minimumDistanceToObstacle(0)
{ }

void DataAnalyserImpl::operator=(const DataAnalyserImpl &)
{ }
