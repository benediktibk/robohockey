#include "layer/dataanalysis/odometryimpl.h"
#include "common/point.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void OdometryImpl::setCurrentPosition(const Point &/*position*/) const
{

}

const Point &OdometryImpl::getCurrentPosition() const
{
	return Point::zero();
}
