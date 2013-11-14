#include "layer/hardware/odometrymock.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Hardware;

OdometryMock::OdometryMock() :
	m_callsToSetCurrentPosition(0),
	m_callsToGetCurrentPosition(0)
{ }

void OdometryMock::setCurrentPosition(const RobotPosition &position)
{
	++m_callsToSetCurrentPosition;
	m_currentPosition = position;
}

RobotPosition OdometryMock::getCurrentPosition()
{
	++m_callsToGetCurrentPosition;
	return m_currentPosition;
}

unsigned int OdometryMock::getCallsToSetCurrentPosition() const
{
	return m_callsToSetCurrentPosition;
}

unsigned int OdometryMock::getCallsToGetCurrentPosition() const
{
	return m_callsToGetCurrentPosition;
}
