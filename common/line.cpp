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
	Point start(m_start - circle.getCenter());
	Point end(m_end - circle.getCenter());
	vector<Point> intersetPoints;
	double gradient = (end.getY() - start.getY())/(end.getX() - start.getX());
	double yAxisIntercept = start.getY() - gradient*start.getX();
	double radius = circle.getDiameter()/2;
	double linearComponent = 2*gradient*yAxisIntercept;
	double squareComponent = gradient*gradient + 1;
	double discriminant = linearComponent*linearComponent - 4*squareComponent*(yAxisIntercept*yAxisIntercept - radius*radius);

	if (discriminant < 0)
		return intersetPoints;
	else
	{
		if (discriminant == 0)
		{
			double resultX = -linearComponent/(2*squareComponent);
			intersetPoints.push_back(Point(resultX, gradient*resultX + yAxisIntercept));
		}
		else
		{
			double resultX1 = (-linearComponent + sqrt(discriminant)) / (2*squareComponent);
			double resultX2 = (-linearComponent - sqrt(discriminant)) / (2*squareComponent);
			intersetPoints.push_back(Point(resultX1, gradient*resultX1 + yAxisIntercept));
			intersetPoints.push_back(Point(resultX2, gradient*resultX2 + yAxisIntercept));
		}
	}
	return intersetPoints;
}
