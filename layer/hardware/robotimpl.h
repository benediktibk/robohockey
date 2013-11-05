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

		virtual Sonar& getSonar();
		virtual Lidar& getLidar();
		virtual Camera& getCamera();
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();
		void updateSensorData();
		virtual bool isValid() const;

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
