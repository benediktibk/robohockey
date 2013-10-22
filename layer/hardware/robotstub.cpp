#include "layer/hardware/robotstub.h"

using namespace RoboHockey::Layer::Hardware;

const Sonar &RobotStub::getSonar() const
{
	return m_sonar;
}

const Lidar &RobotStub::getLidar() const
{
	return m_lidar;
}

const Camera &RobotStub::getCamera() const
{
	return m_camera;
}

const Odometry &RobotStub::getOdometry() const
{
	return m_odometry;
}

Engine &RobotStub::getEngine()
{
	return m_engine;
}
