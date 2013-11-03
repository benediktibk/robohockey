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

Rectangle Circle::getBoundingRectangle() const
{
	double radius = m_diameter/2;
	return Rectangle(m_center - Point(radius, radius), m_center + Point(radius, radius));
}

double Circle::getDistanceTo(const Point &position) const
{
	return position.distanceTo(m_center) - m_diameter/2;
}

