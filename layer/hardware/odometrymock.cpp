#include "layer/hardware/odometrymock.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Hardware;

OdometryMock::OdometryMock() :
	m_callsToSetCurrentPosition(0),
	m_callsToGetCurrentPosition(0),
	m_callsToGetCurrentOrientation(0),
	m_currentOrientation(0)
{ }

void OdometryMock::setCurrentPosition(const Point &position)
{
	++m_callsToSetCurrentPosition;
	m_currentPosition = position;
}

double OdometryMock::getCurrentOrientation()
{
	++m_callsToGetCurrentOrientation;
	return m_currentOrientation;
}

void OdometryMock::setCurrentOrientation(double value)
{
	m_currentOrientation = value;
}

Point OdometryMock::getCurrentPosition()
{
	++m_callsToGetCurrentPosition;
	return m_currentPosition;
}

unsigned int OdometryMock::getCallsToSetCurrentPosition() const
{
	return m_callsToSetCurrentPosition;
}

unsigned int OdometryMock::getCallsToGetCurrentOrientation() const
{
	return m_callsToGetCurrentOrientation;
}

unsigned int OdometryMock::getCallsToGetCurrentPosition() const
{
	return m_callsToGetCurrentPosition;
}
