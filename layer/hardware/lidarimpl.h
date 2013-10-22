#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDARIMPL_H

#include "layer/hardware/lidar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class LidarImpl :
		public Lidar
{
public:
	virtual double getDistance(unsigned int angle) const;
};
}
}
}

#endif
