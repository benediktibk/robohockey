#include "common/path.h"
#include "common/circle.h"
#include "common/line.h"
#include "common/angle.h"
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
	Angle angleBetweenPoints(m_start, m_end);
	Point startLeft(m_start + Point(sqrt(2)*0.5*m_width, Angle::getQuarterRotation() + Angle::getEighthRotation() + angleBetweenPoints));
	Point startRight(m_start + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getQuarterRotation() - Angle::getEighthRotation()));
	Point endLeft(m_end + Point(sqrt(2)*0.5*m_width, Angle::getEighthRotation() + angleBetweenPoints));
	Point endRight(m_end + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getEighthRotation()));
	Line leftOutline(startLeft, endLeft);
	Line rightOutline(startRight, endRight);
	Line startOutline(startLeft, startRight);
	Line endOutline(endLeft, endRight);

	if(isCircleOnPath(circle))
		return true;
	if (leftOutline.getIntersectPoints(circle).size() + rightOutline.getIntersectPoints(circle).size() +
		startOutline.getIntersectPoints(circle).size() + endOutline.getIntersectPoints(circle).size() != 0)
		return true;

	return false;
}

bool Path::intersectsWith(const vector<Circle> &circles) const
{
	for (vector<Circle>::const_iterator i = circles.begin(); i != circles.end(); ++i)
		if (intersectsWith(*i))
			return true;
	return false;
}

bool Path::isCircleOnPath(const Circle &circle) const
{
	Point circleCenter = circle.getCenter();
	Angle angleBetweenPoints(m_start, m_end);
	Point startRight(m_start + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getQuarterRotation() - Angle::getEighthRotation()));

	circleCenter.rotate(Angle::getFullRotation() - angleBetweenPoints);
	circleCenter = circleCenter - startRight;
	if (circleCenter.getX() > 0 && circleCenter.getX() < m_start.distanceTo(m_end) && circleCenter.getY() < m_width)
		return true;
	else
		return false;

}
