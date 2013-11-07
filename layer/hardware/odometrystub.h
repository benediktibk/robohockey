#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYSTUB_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYSTUB_H

#include "layer/hardware/odometry.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class OdometryStub :
		public Odometry
{
public:
	virtual void setCurrentPosition(const Common::Point &position, double orientation);
	virtual Common::Point getCurrentPosition();
	virtual double getCurrentOrientation();
};
}
}
}

#endif
