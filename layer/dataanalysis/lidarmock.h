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
		virtual bool isPuckCollectable(double maximumDistance, const Common::Angle &maximumAngle) const;
		virtual bool isPuckCollected() const;

		void setAllObjects(const LidarObjects &objects);
		void setPuckCollected(bool value);
		void setPuckCollectable(bool value);

	private:
		LidarObjects m_objects;
		bool m_puckCollected;
		bool m_puckCollectable;
	};
}
}
}

#endif
