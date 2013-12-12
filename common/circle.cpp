#include "common/circle.h"
#include "common/compare.h"
#include "common/quadraticequation.h"
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

vector<Point> Circle::getIntersectionPoints(const Circle &circle) const
{
	assert(!(m_center == circle.getCenter()));

	vector<Point> result;
	double x1 = m_center.getX();
	double y1 = m_center.getY();
	double x2 = circle.getCenter().getX();
	double y2 = circle.getCenter().getY();
	double r1 = m_diameter/2;
	double r2 = circle.getDiameter()/2;
	double offsets = ((r1*r1 - r2*r2) - (x1*x1 - x2*x2) - (y1*y1 - y2*y2))/2;
	double lineGradient = (x2 - x1)/(y1 - y2);
	double lineOffset = offsets/(y1 - y2);
	double a = 1 + lineGradient*lineGradient;
	double b = 2*lineGradient*(lineOffset - y1) - 2*x1;
	double c = x1*x1 + (lineOffset - y1)*(lineOffset - y1) - r1*r1;
	QuadraticEquation equation(a, b, c);
	Compare compare(0.0001);
	vector<double> equationSolutions = equation.getSolutions(compare);

	assert(equationSolutions.size() <= 2);

	if (equationSolutions.size() == 0)
		return result;
	else if (equationSolutions.size() == 1)
	{
		double x = equationSolutions.front();
		double y = lineGradient*x + lineOffset;
		result.push_back(Point(x, y));
		return result;
	}
	else
	{
		double x1 = equationSolutions[0];
		double x2 = equationSolutions[1];
		double y1 = lineGradient*x1 + lineOffset;
		double y2 = lineGradient*x2 + lineOffset;
		result.push_back(Point(x1, y1));
		result.push_back(Point(x2, y2));
		return result;
	}
}

bool Circle::isOnCircle(const Point &point, const Compare &compare) const
{
	Point difference = m_center - point;
	double radius = m_diameter/2;
	double leftSideOfEquation = difference.getX()*difference.getX() + difference.getY()*difference.getY();
	double rightSideOfEquation = radius*radius;
	return compare.isFuzzyEqual(leftSideOfEquation, rightSideOfEquation);
}
