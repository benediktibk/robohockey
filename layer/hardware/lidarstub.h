#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDARSTUB_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDARSTUB_H

#include "layer/hardware/lidar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class LidarStub :
			public Lidar
	{
	public:
		virtual double getDistance(unsigned int angle);
	};
}
}
}

#endif
