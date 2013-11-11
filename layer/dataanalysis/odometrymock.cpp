#include "layer/dataanalysis/odometrymock.h"
#include "common/point.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void OdometryMock::setCurrentPosition(const Point &position, double orientation)
{
	m_position = position;
	m_orientation = orientation;
}

Point OdometryMock::getCurrentPosition() const
{
	return m_position;
}

double OdometryMock::getCurrentOrientation() const
{
	return m_orientation;
}
