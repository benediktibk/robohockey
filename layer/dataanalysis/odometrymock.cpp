#include "layer/dataanalysis/odometrymock.h"
#include "common/point.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void OdometryMock::setCurrentPosition(const RobotPosition &position)
{
	m_position = position;
}

RobotPosition OdometryMock::getCurrentPosition() const
{
	return m_position;
}
