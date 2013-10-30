#include "layer/dataanalysis/odometryimpl.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

OdometryImpl::OdometryImpl(Hardware::Odometry &odometry) :
	m_odometry(odometry)
{ }

void OdometryImpl::setCurrentPosition(const Point &/*position*/) const
{

}

const Point &OdometryImpl::getCurrentPosition() const
{
	return Point::zero();
}
