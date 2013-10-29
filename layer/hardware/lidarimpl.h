#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDARIMPL_H

#include "layer/hardware/lidar.h"
#include <player-3.0/libplayerc++/playerc++.h>

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
		LidarImpl(PlayerCc::PlayerClient *playerClient);

		virtual double getDistance(unsigned int angle);

	private:
		PlayerCc::LaserProxy m_laser;
	};
}
}
}

#endif
