#include "common/line.h"
#include "common/circle.h"
#include "common/angle.h"
#include <math.h>
#include "common/compare.h"

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
	vector<Point> intersectPoints;
	Angle angleForVerticalLines;
	double gradient;
	Compare compare(0.001);

	if(compare.isFuzzyEqual(end.getX(), start.getX()))
	{
		gradient = 0;
		angleForVerticalLines = Angle::getThreeQuarterRotation();
		start.rotate(angleForVerticalLines);
		end.rotate(angleForVerticalLines);
	}
	else
	{
		Point startToEndDifference = end - start;
		gradient = startToEndDifference.getY()/startToEndDifference.getX();
	}

	double yAxisIntercept = start.getY() - gradient*start.getX();
	double radius = circle.getDiameter()/2;
	double linearComponent = 2*gradient*yAxisIntercept;
	double squareComponent = gradient*gradient + 1;
	double discriminant = linearComponent*linearComponent - 4*squareComponent*(yAxisIntercept*yAxisIntercept - radius*radius);

	if (discriminant < 0)
		return intersectPoints;
	else
	{
		if (discriminant == 0)
		{
			double resultX = -linearComponent/(2*squareComponent);
			Point result(resultX, gradient*resultX + yAxisIntercept);
			if(angleForVerticalLines.getValueBetweenZeroAndTwoPi() != 0)
				result.rotate(Angle::getQuarterRotation());
			if((compare.isFuzzyGreater(resultX, start.getX()) && compare.isFuzzySmaller(resultX, end.getX())) ||
				(compare.isFuzzySmaller(resultX, start.getX()) && compare.isFuzzyGreater(resultX, end.getX())))
			{
				result = result	+ circle.getCenter();
				intersectPoints.push_back(result);
			}
		}
		else
		{
			double resultX1 = (-linearComponent + sqrt(discriminant)) / (2*squareComponent);
			double resultX2 = (-linearComponent - sqrt(discriminant)) / (2*squareComponent);
			Point resultPlus(resultX1, gradient*resultX1 + yAxisIntercept);
			Point resultMinus(resultX2, gradient*resultX2 + yAxisIntercept);
			if(angleForVerticalLines.getValueBetweenZeroAndTwoPi() != 0)
			{
				resultPlus.rotate(Angle::getQuarterRotation());
				resultMinus.rotate(Angle::getQuarterRotation());
			}
			if((compare.isFuzzyGreater(resultX1, start.getX()) && compare.isFuzzySmaller(resultX1, end.getX())) ||
				(compare.isFuzzySmaller(resultX1, start.getX()) && compare.isFuzzyGreater(resultX1, end.getX())) ||
				(compare.isFuzzyGreater(resultX2, start.getX()) && compare.isFuzzySmaller(resultX2, end.getX())) ||
				(compare.isFuzzySmaller(resultX2, start.getX()) && compare.isFuzzyGreater(resultX2, end.getX())))
			{
				resultPlus = resultPlus + circle.getCenter();
				resultMinus = resultMinus + circle.getCenter();
				intersectPoints.push_back(resultPlus);
				intersectPoints.push_back(resultMinus);
			}
		}
	}
	return intersectPoints;
}

Point Line::getPerpendicularPoint(Point point) const
{
	Angle angleBetweenPoints(m_start, m_end);

	point = point - m_start;
	point.rotate(Angle::getFullRotation() - angleBetweenPoints);

	Point perpendicularPoint(point.getX(),0);
	perpendicularPoint.rotate(angleBetweenPoints);

	return perpendicularPoint;
}

bool Line::isTargetPointRightOfLine(const Point &target)
{
	return 0 < (m_end.getY()*(target.getX() - m_start.getX()) - m_end.getX()*(target.getY() - m_start.getY()));
}
