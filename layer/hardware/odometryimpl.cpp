#include "layer/hardware/odometryimpl.h"
#include "common/point.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;
using namespace PlayerCc;

OdometryImpl::OdometryImpl(PlayerClient *playerClient) :
	m_odometry(new Position2dProxy(playerClient))
{
	// it's necessary to read after subscription but before m_playerOffset is set.
	playerClient->Read();
	m_playerOffset = getCurrentPosition();
}

OdometryImpl::~OdometryImpl()
{
	delete m_odometry;
	m_odometry = 0;
}

void OdometryImpl::setCurrentPosition(const RobotPosition &position)
{
	Point globalPosition(m_odometry->GetXPos(), m_odometry->GetYPos());
	Point newOwnOffset = position.getPosition() - globalPosition + m_playerOffset.getPosition();
	newOwnOffset.rotate(Angle() - position.getOrientation());

	m_ownOffset.setPosition(newOwnOffset);

	Angle globalOrientation(m_odometry->GetYaw());
	m_ownOffset.setOrientation( position.getOrientation() - globalOrientation + m_playerOffset.getOrientation() );
}

OdometryImpl::OdometryImpl(const OdometryImpl &)
{ }

void OdometryImpl::operator=(const OdometryImpl &)
{ }

RobotPosition OdometryImpl::getCurrentPosition()
{
	Point position = Point(m_odometry->GetXPos(), m_odometry->GetYPos()) - m_playerOffset.getPosition();
	position.rotate(Angle() - m_playerOffset.getOrientation());

	position = position  + m_ownOffset.getPosition();
	position.rotate(Angle() + m_ownOffset.getOrientation());

	Angle orientation = Angle(m_odometry->GetYaw()) - m_playerOffset.getOrientation() + m_ownOffset.getOrientation();
	return RobotPosition(position, orientation);
}
