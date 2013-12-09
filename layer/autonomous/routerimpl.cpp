#include "layer/autonomous/routerimpl.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/route.h"
#include "layer/autonomous/routelengthcompare.h"
#include "common/path.h"
#include "common/pathintersectpoints.h"
#include "common/angle.h"
#include <math.h>
#include <assert.h>
#include <algorithm>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

RouterImpl::RouterImpl(double robotWidth) :
	m_robotWidth(robotWidth)
{ }

Route RouterImpl::calculateRoute(const Point &start, const Point &end, const Field &field) const
{
	vector<Route> routes = calculateRoutesRecursive(start, end, field);

	if (routes.size() == 0)
		return Route(m_robotWidth);
	else
	{
		RouteLengthCompare lengthCompare;
		sort(routes.begin(), routes.end(), lengthCompare);
		return routes.front();
	}
}

vector<Point> RouterImpl::getPointsBesideObstacle(const Path &path, const Circle &obstacle) const
{
	vector<Point> pointsBesideObstacle;
	PathIntersectPoints intersectionPoints = path.getIntersectPoints(obstacle);
	Point shortPointBesideObstacle;
	Point longPointBesdieObstacle;
	Point centerBetweenIntersectPoints = (intersectionPoints.front() + intersectionPoints.back())/2;
	double offsetDistanceShortPoint = 0.5*m_robotWidth + centerBetweenIntersectPoints.distanceTo(intersectionPoints.front());;
	double offsetDistanceLongPoint = sqrt(2)*0.5*(m_robotWidth + obstacle.getDiameter()) + 0.5*m_robotWidth;
	Angle offsetAngleShortPoint = path.getAgnleBetweenStartAndEnd();

	assert(intersectionPoints.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeFromStart);
	assert(intersectionPoints.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeFromEnd);

	if(!path.isCircleCenterOnPath(obstacle))
		offsetDistanceLongPoint += centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
	else
	{
		offsetDistanceShortPoint += 2*centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		offsetDistanceLongPoint -= centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
	}
	if(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromLeft)
		offsetAngleShortPoint = offsetAngleShortPoint + Angle::getThreeQuarterRotation();
	else
		offsetAngleShortPoint = offsetAngleShortPoint + Angle::getQuarterRotation();

	shortPointBesideObstacle = centerBetweenIntersectPoints + Point(offsetDistanceShortPoint, offsetAngleShortPoint);
	longPointBesdieObstacle = centerBetweenIntersectPoints + Point(offsetDistanceLongPoint, offsetAngleShortPoint + Angle::getHalfRotation());

	pointsBesideObstacle.push_back(shortPointBesideObstacle);
	pointsBesideObstacle.push_back(longPointBesdieObstacle);
	return pointsBesideObstacle;
}

vector<Route> RouterImpl::calculateRoutesRecursive(const Point &/*start*/, const Point /*end*/, const Field &/*field*/) const
{
	return vector<Route>();
}
