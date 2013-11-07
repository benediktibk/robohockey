#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H

#include "layer/autonomous/field.h"

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
}
namespace Layer
{
namespace DataAnalysis
{
	class LidarImpl;
	class SonarImpl;
	class OdometryImpl;
	class CameraImpl;
}

namespace Autonomous
{
	class FieldImpl :
			public Field
	{
	public:
		FieldImpl(DataAnalysis::OdometryImpl &odometry, DataAnalysis::LidarImpl &lidar, DataAnalysis::CameraImpl &camera);
		virtual void update();

	private:
		virtual void updateWithLidarData();
		virtual void updateWithOdometryData();

	private:
		DataAnalysis::OdometryImpl *m_odometry;
		DataAnalysis::LidarImpl *m_lidar;
		DataAnalysis::CameraImpl *m_camera;

		Common::RobotPosition *m_position;
	};
}
}
}

#endif
