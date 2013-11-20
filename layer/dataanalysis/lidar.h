#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H

#include "layer/dataanalysis/lidarobjects.h"

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
	class Lidar
	{
	public:
		virtual ~Lidar() { }

		/*!
		 * The orientation is relative to the axis, therefore lookin in the direction of the x-axis means 0 orienation.
		 * All other orientations are in mathematical positive direction.
		 */
		virtual LidarObjects getAllObjects(const Common::RobotPosition &ownPosition) const = 0;
		virtual bool isObstacleInFront() const = 0;
	};
}
}
}

#endif
