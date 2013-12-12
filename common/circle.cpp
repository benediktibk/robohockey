#include "common/circle.h"
#include "common/compare.h"
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;

Circle::Circle() :
	m_diameter(0)
{ }

Circle::Circle(const Point &center, double diameter) :
	m_center(center),
	m_diameter(diameter)
{
	assert(m_diameter >= 0);
}

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
	assert(m_diameter >= 0);
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

bool Circle::overlapsWith(const Circle &/*circle*/) const
{
	return false;
}

vector<Point> Circle::getIntersectionPoints(const Circle &/*circle*/) const
{
	vector<Point> result;
	return result;
}

bool Circle::isOnCircle(const Point &/*point*/, const Compare &/*compare*/) const
{
	return false;
}
