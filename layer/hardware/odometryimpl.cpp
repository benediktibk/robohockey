#include "layer/hardware/odometryimpl.h"
#include "common/point.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;
using namespace PlayerCc;

OdometryImpl::OdometryImpl(PlayerClient *playerClient) :
	m_odometry(new Position2dProxy(playerClient)),
	m_playerOrientationOffset(0),
	m_ownOrientationOffset(0)
{
	m_odometry->ResetOdometry();
	playerClient->Read();
	m_playerPositionOffset = getCurrentPosition();
	m_playerOrientationOffset = getCurrentOrientation();
}

OdometryImpl::~OdometryImpl()
{
	delete m_odometry;
	m_odometry = 0;
}

void OdometryImpl::setCurrentPosition(const Point &position, double orientation)
{
	m_ownPositionOffset = position;
	m_ownOrientationOffset = orientation;
}

double OdometryImpl::getCurrentOrientation()
{
	return m_odometry->GetYaw() - m_playerOrientationOffset - m_ownOrientationOffset;
}

OdometryImpl::OdometryImpl(const OdometryImpl &)
{ }

void OdometryImpl::operator=(const OdometryImpl &)
{ }

Point OdometryImpl::getCurrentPosition()
{
	return Point(m_odometry->GetXPos(), m_odometry->GetYPos()) - m_playerPositionOffset - m_ownPositionOffset;
}
