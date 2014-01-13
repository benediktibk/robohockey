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
	m_engine = new EngineImpl(m_playerClient);
	m_playerClient->Read(); // don't call this before any proxy is subscribed, otherwise it will wait forever
	m_sonar = new SonarImpl(m_playerClient);
	m_lidar = new LidarImpl(m_playerClient);
	m_camera = new CameraImpl(0);
	m_odometry = new OdometryImpl(m_playerClient);

	sleep(5); // wait till the lidar startup is done
	updateSensorData(); // fetch reasonable values
	updateSensorData(); // call it a second time to have current and last values in the sonar
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

const Odometry &RobotImpl::getOdometry() const
{
	return *m_odometry;
}

const Engine &RobotImpl::getEngine() const
{
	return *m_engine;
}

void RobotImpl::updateSensorData()
{
	m_playerClient->Read();
	m_sonar->updateSensorData();
	m_engine->updateSensorData();
}

RobotImpl::RobotImpl(const RobotImpl &)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
