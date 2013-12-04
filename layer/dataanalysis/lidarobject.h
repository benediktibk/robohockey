#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECT_H

#include "common/circle.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarObject :
			public Common::Circle
	{
	public:
		LidarObject();
		LidarObject(const Common::Point &position, double diameter);
	};
}
}
}


#endif
