#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H

#include "layer/hardware/odometry.h"

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
	virtual void setCurrentPosition(const Common::Point &position) const;
	virtual const Common::Point& getCurrentPosition() const;
};
}
}
}

#endif
