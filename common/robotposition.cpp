#include "common/robotposition.h"
#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;

RobotPosition::RobotPosition():
	Point(),
	m_orientation(0)
{ }

RobotPosition::RobotPosition(double x, double y):
	Point(x, y),
	m_orientation(0)
{ }

RobotPosition::RobotPosition(double x, double y, double orientation):
	Point(x, y),
	m_orientation(orientation)
{ }

void RobotPosition::setOrientation(double orientation)
{
	m_orientation = orientation;
}

double RobotPosition::getOrientation() const
{
	return m_orientation;
}

bool RobotPosition::operator ==(const RobotPosition &position) const
{
	Compare compare(0.00001);
	return compare.isFuzzyEqual(*this, position);
}

RobotPosition RobotPosition::operator *(double value) const
{
	return RobotPosition(getX()*value, getY()*value, m_orientation);
}

RobotPosition RobotPosition::operator /(double value) const
{
	return RobotPosition(getX()/value, getY()/value, m_orientation);
}

RobotPosition RobotPosition::operator +(const RobotPosition &point) const
{
	return RobotPosition(getX()+point.getX(), getY()+point.getY(), 0);

}

RobotPosition RobotPosition::operator -(const RobotPosition &point) const
{
	return RobotPosition(getX()-point.getX(), getY()-point.getY(), 0);

}

void RobotPosition::operator *=(double value)
{
	*this = *this*value;
}

double RobotPosition::distanceTo(const RobotPosition &point) const
{
	Point difference = *this - point;
	return sqrt(difference.getX()*difference.getX() + difference.getY()*difference.getY());

}
