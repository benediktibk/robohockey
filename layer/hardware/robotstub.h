#ifndef ROBOHOCKEY_LAYER_HARDWARE_ROBOTSTUB_H
#define ROBOHOCKEY_LAYER_HARDWARE_ROBOTSTUB_H

#include "layer/hardware/robot.h"
#include "layer/hardware/sonarstub.h"
#include "layer/hardware/lidarstub.h"
#include "layer/hardware/camerastub.h"
#include "layer/hardware/odometrystub.h"
#include "layer/hardware/enginestub.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class RobotStub :
			public Robot
	{
	public:
		virtual Sonar& getSonar();
		virtual Lidar& getLidar();
		virtual Camera& getCamera();
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();

	private:
		SonarStub m_sonar;
		LidarStub m_lidar;
		CameraStub m_camera;
		OdometryStub m_odometry;
		EngineStub m_engine;
	};
}
}
}

#endif
