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
		virtual LidarObjects getAllObjects(const Common::Point &ownPosition, double ownOrientation) const;
	};
}
}
}

#endif
