#include "layer/hardware/odometryimpl.h"
#include "common/point.h"

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;

void OdometryImpl::setCurrentPosition(const Point &/*position*/) const
{

}

const Point &OdometryImpl::getCurrentPosition() const
{
	return Point::zero();
}
