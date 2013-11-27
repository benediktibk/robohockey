#include "common/line.h"
#include "common/circle.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace std;

Line::Line(const Point &start, const Point &end) :
	m_start(start),
	m_end(end)
{ }

vector<Point> Line::getIntersectPoints(const Circle &circle) const
{
	Circle circleWithOriginZero(Point(0,0), circle.getDiameter());
	Point start(m_start - circle.getCenter());
	Point end(m_end - circle.getCenter());
	vector<Point> intersetPoints;
	double gradient = (end.getY() - start.getY())/(end.getY() - start.getY());
	double yAxisIntercept = start.getY() - gradient*start.getX();
	double radius = circleWithOriginZero.getDiameter()/2;
	double discriminant = -4 * (gradient*gradient + 1) + (yAxisIntercept*yAxisIntercept - radius*radius);

	if (discriminant < 0)
		return intersetPoints;
	else
	{
		double resultX = sqrt((radius*radius - yAxisIntercept*yAxisIntercept)/(gradient*gradient + 1));
		double resultY1 = gradient*resultX + yAxisIntercept;
		if (discriminant == 0)
			intersetPoints.push_back(Point(resultX, resultY1));
		else
		{
			intersetPoints.push_back(Point(resultX, resultY1));
			intersetPoints.push_back(Point(-resultX, gradient*(-resultX) + yAxisIntercept));
		}
	}
	return intersetPoints;
}
