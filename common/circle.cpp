#include "common/circle.h"

using namespace RoboHockey::Common;

Circle::Circle() :
	m_diameter(0)
{ }

Circle::Circle(const Point &center, double diameter) :
	m_center(center),
	m_diameter(diameter)
{ }

void Circle::setCenter(const Point &point)
{
	m_center = point;
}

const Point &Circle::getCenter() const
{
	return m_center;
}

void Circle::setDiameter(double value)
{
	m_diameter = value;
}

double Circle::getDiameter() const
{
	return m_diameter;
}
