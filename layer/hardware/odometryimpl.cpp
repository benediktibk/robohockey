#include "layer/hardware/odometryimpl.h"
#include "common/point.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;
using namespace PlayerCc;

OdometryImpl::OdometryImpl(PlayerClient *playerClient) :
	m_odometry(new Position2dProxy(playerClient))
{
}

OdometryImpl::~OdometryImpl()
{
	delete m_odometry;
	m_odometry = 0;
}

void OdometryImpl::setCurrentPosition(const Point &position)
{
	m_odometry->ResetOdometry();
    m_odometry->SetOdometry(position.getX(), position.getY(), 0);
}
double OdometryImpl::getCurrentOrientation()
{
    return m_odometry->GetYaw();
}

const Point &OdometryImpl::getCurrentPosition()
{
	return *(new const Point(m_odometry->GetXPos(), m_odometry->GetYPos()));
}
