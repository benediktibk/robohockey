#include "common/path.h"
#include "common/circle.h"
#include "common/line.h"
#include "common/angle.h"
#include "common/pathintersectpoints.h"
#include <math.h>

using namespace std;
using namespace RoboHockey::Common;

Path::Path(const Point &start, const Point &end, double width) :
	m_start(start),
	m_end(end),
	m_width(width)
{ }

bool Path::intersectsWith(const Circle &circle) const
{
	if(isCircleCenterOnPath(circle))
		return true;
	if (getIntersectPoints(circle).getIntersectPointsCount() != 0)
		return true;

	return false;
}

bool Path::isCircleCenterOnPath(const Circle &circle) const
{
	Point circleCenter = circle.getCenter();
	Angle angleBetweenPoints(m_start, m_end);

	circleCenter = circleCenter - m_start;
	circleCenter.rotate(Angle::getFullRotation() - angleBetweenPoints);
	if (circleCenter.getX() > -0.5*m_width && circleCenter.getX() < (m_start.distanceTo(m_end) + 0.5*m_width) && fabs(circleCenter.getY()) < 0.5*m_width)
		return true;
	else
		return false;
}

PathIntersectPoints Path::getIntersectPoints(const Circle &circle) const
{
	Angle angleBetweenPoints(m_start, m_end);
	Point startLeft(m_start + Point(sqrt(2)*0.5*m_width, Angle::getQuarterRotation() + Angle::getEighthRotation() + angleBetweenPoints));
	Point startRight(m_start + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getQuarterRotation() - Angle::getEighthRotation()));
	Point endLeft(m_end + Point(sqrt(2)*0.5*m_width, Angle::getEighthRotation() + angleBetweenPoints));
	Point endRight(m_end + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getEighthRotation()));
	Line leftOutline(startLeft, endLeft);
	Line rightOutline(startRight, endRight);
	Line startOutline(startLeft, startRight);
	Line endOutline(endLeft, endRight);

	PathIntersectPoints intersectPointsLeft(leftOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromLeft);
	if(intersectPointsLeft.getIntersectPointsCount() != 0)
		return intersectPointsLeft;
	PathIntersectPoints intersectPointsRight(rightOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromRight);
	if(intersectPointsRight.getIntersectPointsCount() != 0)
		return intersectPointsRight;
	PathIntersectPoints intersectPointsStart(startOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromStart);
	if(intersectPointsStart.getIntersectPointsCount() != 0)
		return intersectPointsStart;
	PathIntersectPoints intersectPointsEnd(endOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromEnd);
	if(intersectPointsEnd.getIntersectPointsCount() != 0)
		return intersectPointsEnd;

	return PathIntersectPoints(vector<Point>(), PathIntersectPoints::IntersectTypeNoIntersect);
}

Angle Path::getAngleBetweenStartAndEnd() const
{
	return Angle(m_start, m_end);
}

Point Path::getLeftPerpendicularPoint(const Point &point) const
{
	Angle angleBetweenPoints(m_start, m_end);
	Point startLeft(m_start + Point(sqrt(2)*0.5*m_width, Angle::getQuarterRotation() + Angle::getEighthRotation() + angleBetweenPoints));
	Point endLeft(m_end + Point(sqrt(2)*0.5*m_width, Angle::getEighthRotation() + angleBetweenPoints));
	Line leftOutline(startLeft, endLeft);

	return leftOutline.getPerpendicularPoint(point);
}

Point Path::getRightPerpendicularPoint(const Point &point) const
{
	Angle angleBetweenPoints(m_start, m_end);
	Point startRight(m_start + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getQuarterRotation() - Angle::getEighthRotation()));
	Point endRight(m_end + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getEighthRotation()));
	Line rightOutline(startRight, endRight);

	return rightOutline.getPerpendicularPoint(point);
}

double Path::getDistanceToLeftPerpendicularPoint(const Point &point) const
{
	return point.distanceTo(getLeftPerpendicularPoint(point));
}

double Path::getDistanceToRightPerpendicularPoint(const Point &point) const
{
	return point.distanceTo(getRightPerpendicularPoint(point));
}

Line Path::getCenterLine() const
{
	return Line(m_start, m_end);
}
