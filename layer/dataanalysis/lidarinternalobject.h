#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARINTERNALOBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARINTERNALOBJECT_H

#include "common/angle.h"

namespace RoboHockey
{
namespace Common
{
	class Point;
}

namespace Layer
{
namespace DataAnalysis
{
	class LidarInternalObject
	{
	public:
		LidarInternalObject();
		LidarInternalObject(const Common::Angle &width, const Common::Angle &orientation, double distance);

		double getWidthInMeter() const;
		Common::Point getPositionRelativeToRobot() const;
		const Common::Angle& getOrientationRelativeToRobot() const;
		double getDistance() const;

	private:
		void calculateWidthInMeter();

	private:
		Common::Angle m_width;
		Common::Angle m_orientationRelativeToRobot;
		double m_distance;
		double m_widthInMeter;
	};
}
}
}

#endif
