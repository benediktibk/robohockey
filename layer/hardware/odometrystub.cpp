#include "layer/hardware/odometrystub.h"
#include "common/point.h"

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;

void OdometryStub::setCurrentPosition(const Point &/*position*/) const
{ }

const Point &OdometryStub::getCurrentPosition() const
{
	return Point::zero();
}