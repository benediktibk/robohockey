#include "layer/hardware/robotstub.h"

using namespace RoboHockey::Layer::Hardware;

Sonar &RobotStub::getSonar()
{
	return m_sonar;
}

Lidar &RobotStub::getLidar()
{
	return m_lidar;
}

Camera &RobotStub::getCamera()
{
	return m_camera;
}

Odometry &RobotStub::getOdometry()
{
	return m_odometry;
}

Engine &RobotStub::getEngine()
{
	return m_engine;
}

bool RobotStub::isValid() const
{
	return true;
}
