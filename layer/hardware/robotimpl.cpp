#include "layer/hardware/robotimpl.h"
#include "layer/hardware/sonarimpl.h"
#include "layer/hardware/lidarimpl.h"
#include "layer/hardware/cameraimpl.h"
#include "layer/hardware/odometryimpl.h"
#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace std;

RobotImpl::RobotImpl(const string &playerServer)
{
	m_playerClient = new PlayerCc::PlayerClient(playerServer.c_str(), 6665);
	m_sonar = new SonarImpl(m_playerClient);
	m_lidar = new LidarImpl(m_playerClient);
	m_camera = new CameraImpl(0);
	m_odometry = new OdometryImpl(m_playerClient);
	m_engine = new EngineImpl(m_playerClient);

	updateSensorData();
	sleep(5);
	updateSensorData();
}

RobotImpl::~RobotImpl()
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
	delete m_playerClient;
	m_playerClient = 0;
}

Sonar &RobotImpl::getSonar()
{
	return *m_sonar;
}

Lidar &RobotImpl::getLidar()
{
	return *m_lidar;
}

Camera &RobotImpl::getCamera()
{
	return *m_camera;
}

Odometry &RobotImpl::getOdometry()
{
	return *m_odometry;
}

Engine &RobotImpl::getEngine()
{
	return *m_engine;
}

void RobotImpl::updateSensorData()
{
	m_playerClient->Read();
}

RobotImpl::RobotImpl(const RobotImpl &)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
