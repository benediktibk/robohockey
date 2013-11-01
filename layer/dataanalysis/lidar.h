#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H

#include "layer/dataanalysis/lidarobjects.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class Lidar
	{
	public:
		virtual ~Lidar() { }

		virtual LidarObjects getAllObjects(const Common::Point &ownPosition) const = 0;
	};
}
}
}

#endif
