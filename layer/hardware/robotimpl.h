#ifndef ROBOHOCKEY_LAYER_HARDWARE_ROBOTIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ROBOTIMPL_H

#include "layer/hardware/robot.h"
#include <string>

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
		RobotImpl(const std::string &playerServer);
		~RobotImpl();

		virtual Sonar& getSonar();
		virtual Lidar& getLidar();
		virtual Camera& getCamera();
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();
		virtual const Sonar& getSonar() const;
		virtual const Lidar& getLidar() const;
		virtual const Camera& getCamera() const;
		virtual const Odometry& getOdometry() const;
		virtual const Engine& getEngine() const;
		virtual void updateSensorData();

	private:
		// forbid copies
		RobotImpl(const RobotImpl &robot);
		void operator=(const RobotImpl &robot);

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
