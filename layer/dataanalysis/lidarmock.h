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
		virtual bool isPuckCollectable() const;
		virtual bool isPuckCollected() const;

		void setAllObjects(const LidarObjects &objects);
		void setPuckCollected(bool value);

	private:
		LidarObjects m_objects;
		bool m_puckCollected;
	};
}
}
}

#endif
