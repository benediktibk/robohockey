#include "layer/autonomous/router.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/route.h"
#include "common/path.h"
#include "common/pathintersectpoints.h"
#include "common/angle.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

Router::Router(double robotWidth, const Field &field) :
	m_field(field),
	m_robotWidth(robotWidth)
{ }

Route Router::calculateRoute(const Point &/*start*/, const Point &end) const
{
	vector<Circle> obstacles = m_field.getAllObstacles();
	Route route(m_robotWidth);
	route.addPoint(end);

	if (route.intersectsWith(obstacles))
		return Route(m_robotWidth);
	else
		return route;
}

vector<Point> Router::getPointsBesideObstacle(const Path &path, const Circle &obstacle) const
{
	PathIntersectPoints intersectionPoints = path.getIntersectPoints(obstacle);
	Angle angleBetweenCircleCenterAndIntersectPoint(obstacle.getCenter(), intersectionPoints.getIntersectPoints().front());
	Point shortPointBesideObstacle;
	Point longPointBesdieObstacle;

	if(path.isCircleCenterOnPath(obstacle))
	{
		if(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromLeft)
		{
			shortPointBesideObstacle = (intersectionPoints.front() + intersectionPoints.back())/2;
			shortPointBesideObstacle = shortPointBesideObstacle + Point(0.5*m_robotWidth, Angle::getThreeQuarterRotation() + path.getAgnleBetweenStartAndEnd());
		}
	}
	else
	{

	}


	return vector<Point>();
}
