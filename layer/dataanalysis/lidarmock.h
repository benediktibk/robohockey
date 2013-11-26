#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARMOCK_H

#include "layer/dataanalysis/lidar.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarMock :
			public Lidar
	{
	public:
		LidarMock();

		virtual LidarObjects getAllObjects(const Common::RobotPosition &ownPosition) const;
		virtual bool isObstacleInFront(double speed) const;
		virtual void updateSensorData();

		void setAllObjects(const LidarObjects &objects);

	private:
		LidarObjects m_objects;
	};
}
}
}

#endif
