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
	Point pointOnObstacleEdge;

	if(intersectionPoints.getIntersectPointsCount() == 1)
	{
		pointOnObstacleEdge = intersectionPoints.getIntersectPoints().front();
		switch (intersectionPoints.getIntersectTypeFrom()) {
		case PathIntersectPoints::IntersectTypeFromLeft:
			pointOnObstacleEdge = pointOnObstacleEdge + Point(1.2*m_robotWidth, Angle::getFullRotation());
			break;
		case PathIntersectPoints::IntersectTypeFromRight:
			break;
		case PathIntersectPoints::IntersectTypeFromStart:
			break;
		case PathIntersectPoints::IntersectTypeFromEnd:
			break;
		}
	}
	else
	{

	}

	return vector<Point>();
}
