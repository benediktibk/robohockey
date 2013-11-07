#include "common/robotposition.h"

using namespace RoboHockey::Common;

RobotPosition::RobotPosition():
	Point()
{ }

RobotPosition::RobotPosition(double x, double y, double orientation):
	Point(x, y),
	m_orientation(orientation)
{ }

void RobotPosition::setOrientation(double orientation)
{
	m_orientation = orientation;
}

double RobotPosition::getOrientation()
{
	return m_orientation;
}
