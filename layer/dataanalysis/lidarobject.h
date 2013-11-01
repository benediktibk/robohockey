#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECT_H

#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarObject
	{
	public:
		LidarObject();
		LidarObject(const Common::Point &position, double diameter);

		const Common::Point& getPosition() const;
		double getDiameter() const;
		double getDistanceTo(const Common::Point &position) const;

	private:
		Common::Point m_position;
		double m_diameter;
	};
}
}
}


#endif
