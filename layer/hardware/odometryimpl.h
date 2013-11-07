#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H

#include "layer/hardware/odometry.h"
#include "common/point.h"

namespace PlayerCc
{
	class PlayerClient;
	class Position2dProxy;
}

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class OdometryImpl :
			public Odometry
	{
	public:
		OdometryImpl(PlayerCc::PlayerClient *playerClient);
		~OdometryImpl();

		virtual void setCurrentPosition(const Common::Point &position, double orientation);
		virtual Common::Point getCurrentPosition();
		virtual double getCurrentOrientation();

	private:
		PlayerCc::Position2dProxy *m_odometry;
		Common::Point m_playerPositionOffset;
		Common::Point m_ownPositionOffset;
		double m_playerOrientationOffset;
		double m_ownOrientationOffset;
	};
}
}
}

#endif
