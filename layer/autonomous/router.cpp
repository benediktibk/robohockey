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
	vector<Point> pointsBesideObstacle;
	PathIntersectPoints intersectionPoints = path.getIntersectPoints(obstacle);
	Point shortPointBesideObstacle;
	Point longPointBesdieObstacle;
	double offsetDistance;
	Angle offsetAngle;

	if(!path.isCircleCenterOnPath(obstacle))
	{
		shortPointBesideObstacle = (intersectionPoints.front() + intersectionPoints.back())/2;
		offsetDistance = 0.5*m_robotWidth + shortPointBesideObstacle.distanceTo(intersectionPoints.front());
		if(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromLeft)
		{
			offsetAngle = Angle::getThreeQuarterRotation();
		}
		else
		{
			offsetAngle = Angle::getQuarterRotation();
		}
		shortPointBesideObstacle = shortPointBesideObstacle + Point(offsetDistance, offsetAngle + path.getAgnleBetweenStartAndEnd());
	}
	else
	{

	}

	pointsBesideObstacle.push_back(shortPointBesideObstacle);
	return pointsBesideObstacle;
}
