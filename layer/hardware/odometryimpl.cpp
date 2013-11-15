#include "layer/hardware/odometryimpl.h"
#include "common/point.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;
using namespace PlayerCc;

OdometryImpl::OdometryImpl(PlayerClient *playerClient) :
	m_odometry(new Position2dProxy(playerClient))
{
	playerClient->Read();
	m_odometry->ResetOdometry();
	m_playerOffset = getCurrentPosition();
}

OdometryImpl::~OdometryImpl()
{
	delete m_odometry;
	m_odometry = 0;
}

void OdometryImpl::setCurrentPosition(const RobotPosition &position)
{
	m_ownOffset = position;
}

OdometryImpl::OdometryImpl(const OdometryImpl &)
{ }

void OdometryImpl::operator=(const OdometryImpl &)
{ }

RobotPosition OdometryImpl::getCurrentPosition()
{
	Point position = Point(m_odometry->GetXPos(), m_odometry->GetYPos()) - m_playerOffset.getPosition() - m_ownOffset.getPosition();
	Angle orientation = Angle(m_odometry->GetYaw()) - m_playerOffset.getOrientation() - m_ownOffset.getOrientation();
	return RobotPosition(position, orientation);
}
