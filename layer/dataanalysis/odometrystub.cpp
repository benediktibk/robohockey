#include "layer/dataanalysis/odometrystub.h"
#include "common/point.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void OdometryStub::setCurrentPosition(const Point &, double) const
{ }

Point OdometryStub::getCurrentPosition() const
{
	return Point::zero();
}
