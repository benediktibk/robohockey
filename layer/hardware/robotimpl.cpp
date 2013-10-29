#include "layer/hardware/robotimpl.h"
#include "layer/hardware/sonarimpl.h"
#include "layer/hardware/lidarimpl.h"
#include "layer/hardware/cameraimpl.h"
#include "layer/hardware/odometryimpl.h"
#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;

RobotImpl::RobotImpl() :
	m_sonar(new SonarImpl(m_playerClient)),
	m_lidar(new LidarImpl(m_playerClient)),
	m_camera(new CameraImpl(m_playerClient)),
	m_odometry(new OdometryImpl),
	m_engine(new EngineImpl(m_playerClient)),
	m_playerClient(new PlayerCc::PlayerClient("localhost", 6665))
{
	m_playerClient->Read();
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

const Sonar &RobotImpl::getSonar() const
{
	return *m_sonar;
}

const Lidar &RobotImpl::getLidar() const
{
	return *m_lidar;
}

const Camera &RobotImpl::getCamera() const
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
