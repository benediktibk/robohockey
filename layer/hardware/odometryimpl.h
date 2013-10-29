#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H

#include "layer/hardware/odometry.h"
#include <player-3.0/libplayerc++/playerc++.h>

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

	virtual void setCurrentPosition(const Common::Point &position);
	virtual const Common::Point& getCurrentPosition();

private:
	PlayerCc::Position2dProxy m_odometry;
};
}
}
}

#endif
