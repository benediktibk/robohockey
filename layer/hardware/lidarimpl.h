#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDARIMPL_H

#include "layer/hardware/lidar.h"

namespace PlayerCc
{
	class PlayerClient;
	class RangerProxy;
}
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
		~LidarImpl();

		virtual double getDistance(int angle) const;
		virtual void writeDataToFile(const std::string &fileName) const;

	private:
		// forbid copies
		LidarImpl(const LidarImpl &lidar);
		void operator=(const LidarImpl &lidar);

	private:
		PlayerCc::RangerProxy *m_laser;
	};
}
}
}

#endif
