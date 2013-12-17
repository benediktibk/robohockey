#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H

#include "layer/dataanalysis/lidarobjects.h"

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
	class Angle;
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
		virtual bool isObstacleInFront(double speed) const = 0;
		virtual void updateSensorData() = 0;
		virtual bool isPuckCollectable(double maximumDistance, const Common::Angle &maximumAngle) const = 0;
		virtual bool isPuckCollected() const = 0;
		//! Be careful, this one will usually be negative (in terms of mathematical positive direction)
		virtual Common::Angle getMaximumAngleRight() const = 0;
		virtual Common::Angle getMaximumAngleLeft() const = 0;
		virtual bool canBeSeen(const Common::Circle &object) const = 0;
	};
}
}
}

#endif
