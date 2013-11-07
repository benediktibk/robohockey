#include "layer/hardware/odometrystub.h"
#include "common/point.h"

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;

void OdometryStub::setCurrentPosition(const Point &/*position*/)
{ }

Point OdometryStub::getCurrentPosition()
{
	return Point::zero();
}

double OdometryStub::getCurrentOrientation()
{
	return 0;
}
