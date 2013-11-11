#include "layer/dataanalysis/odometrymock.h"
#include "common/point.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void OdometryMock::setCurrentPosition(const Point &position, double)
{
	m_position = position;
}

Point OdometryMock::getCurrentPosition() const
{
	return m_position;
}
