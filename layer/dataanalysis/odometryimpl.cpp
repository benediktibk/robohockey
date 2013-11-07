#include "layer/dataanalysis/odometryimpl.h"
#include "common/point.h"
#include "layer/hardware/odometryimpl.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

OdometryImpl::OdometryImpl(Hardware::Odometry &odometry) :
	m_odometry(odometry)
{ }

void OdometryImpl::setCurrentPosition(const Point &position, double orientation) const
{
	m_odometry.setCurrentPosition(position, orientation);
}

Point OdometryImpl::getCurrentPosition() const
{
	return m_odometry.getCurrentPosition();
}
