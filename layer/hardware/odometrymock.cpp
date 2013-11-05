#include "layer/hardware/odometrymock.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Hardware;

OdometryMock::OdometryMock() :
	m_callsToSetCurrentPosition(0),
    m_callsToGetCurrentPosition(0),
    m_callsToGetCurrentOrientation(0)
{ }

void OdometryMock::setCurrentPosition(const Point &)
{
	++m_callsToSetCurrentPosition;
}

double OdometryMock::getCurrentOrientation()
{
    ++m_callsToGetCurrentOrientation;
    return 0;
}

const Point &OdometryMock::getCurrentPosition()
{
	++m_callsToGetCurrentPosition;
	return Point::zero();
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
