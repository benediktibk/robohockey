#ifndef ROBOHOCKEY_LAYER_HARDWARE_ROBOTIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ROBOTIMPL_H

#include "layer/hardware/robot.h"

namespace PlayerCc
{
class PlayerClient;
}

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class RobotImpl :
		public Robot
{
public:
	RobotImpl();
	~RobotImpl();

	virtual const Sonar& getSonar() const;
	virtual const Lidar& getLidar() const;
	virtual const Camera& getCamera() const;
	virtual Odometry& getOdometry();
	virtual Engine& getEngine();

private:
	Sonar *m_sonar;
	Lidar *m_lidar;
	Camera *m_camera;
	Odometry *m_odometry;
	Engine *m_engine;
	PlayerCc::PlayerClient *m_playerClient;
};
}
}
}

#endif
