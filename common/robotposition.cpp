#include "common/robotposition.h"
#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace std;

RobotPosition::RobotPosition()
{ }

RobotPosition::RobotPosition(const Point &point, const Angle &orientation):
	m_position(point),
	m_orientation(orientation)
{ }

void RobotPosition::setOrientation(const Angle &orientation)
{
	m_orientation = orientation;
}

const Angle& RobotPosition::getOrientation() const
{
	return m_orientation;
}

void RobotPosition::setPosition(const Point &position)
{
	m_position = position;
}

const Point &RobotPosition::getPosition() const
{
	return m_position;
}

bool RobotPosition::operator ==(const RobotPosition &position) const
{
	Compare compare(0.00001);
	return compare.isFuzzyEqual(*this, position);
}

RobotPosition RobotPosition::operator*(double value) const
{
	return RobotPosition(m_position*value, m_orientation);
}

RobotPosition RobotPosition::operator/(double value) const
{
	return RobotPosition(m_position/value, m_orientation);
}

RobotPosition RobotPosition::operator+(const RobotPosition &point) const
{
	return RobotPosition(m_position + point.getPosition(), 0);
}

RobotPosition RobotPosition::operator-(const RobotPosition &point) const
{
	return RobotPosition(m_position - point.getPosition(), 0);
}

void RobotPosition::operator *=(double value)
{
	m_position *= value;
}

RobotPosition::operator Point() const
{
	return m_position;
}

double RobotPosition::distanceTo(const RobotPosition &point) const
{
	return m_position.distanceTo(point.getPosition());
}

ostream &operator<<(ostream &stream, const RobotPosition &point)
{
	const Point &position = point.getPosition();
	stream << "(" << position.getX() << ", " << position.getY() << ", " << point.getOrientation() << ")";
	return stream;
}
