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
	RobotPosition globalPositionAfterPlayerOffset = getGlobalPositionAfterPlayerOffset();
	Point currentPosition = globalPositionAfterPlayerOffset.getPosition();
	Angle deltaAlpha = position.getOrientation() - globalPositionAfterPlayerOffset.getOrientation();

	currentPosition.rotate(deltaAlpha);

	Point newOwnOffset = position.getPosition() - currentPosition;

	m_ownOffset.setPosition(newOwnOffset);

	m_ownOffset.setOrientation(position.getOrientation() - getCurrentPosition().getOrientation() + m_ownOffset.getOrientation());
}

OdometryImpl::OdometryImpl(const OdometryImpl &)
{ }

void OdometryImpl::operator=(const OdometryImpl &)
{ }

const RobotPosition OdometryImpl::getGlobalPositionAfterPlayerOffset() const
{
	Point position = Point(m_odometry->GetXPos(), m_odometry->GetYPos()) - m_playerOffset.getPosition();
	Angle orientation = Angle(m_odometry->GetYaw()) - m_playerOffset.getOrientation();

	position.rotate(Angle() - m_playerOffset.getOrientation());

	return RobotPosition(position, orientation);
}

RobotPosition OdometryImpl::getCurrentPosition()
{
	RobotPosition globalPositionAfterPlayerOffset = getGlobalPositionAfterPlayerOffset();
	Point position = globalPositionAfterPlayerOffset.getPosition();

	position.rotate(m_ownOffset.getOrientation());
	position = position  + m_ownOffset.getPosition();

	Angle orientation = globalPositionAfterPlayerOffset.getOrientation();
	orientation = orientation + m_ownOffset.getOrientation();
	return RobotPosition(position, orientation);
}
