#include "layer/hardware/odometryimpl.h"
#include "common/point.h"

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;

OdometryImpl::OdometryImpl(PlayerCc::PlayerClient *playerClient) :
	m_odometry(playerClient)
{
}

void OdometryImpl::setCurrentPosition(const Point &/*position*/) const
{

}

const Point &OdometryImpl::getCurrentPosition() const
{
	return *(new const Point(m_odometry.GetXPos(), m_odometry.GetYPos()));
}
