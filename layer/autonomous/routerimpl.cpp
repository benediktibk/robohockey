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
#include <limits>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

RouterImpl::RouterImpl(double robotWidth) :
	m_robotWidth(robotWidth)
{ }

Route RouterImpl::calculateRoute(const Point &start, const Point &end, const Field &field) const
{
	Path startPart(start, start, m_robotWidth);
	const vector<Circle> obstacles = field.getAllObstacles();

	if (startPart.intersectsWith(obstacles))
		return Route(m_robotWidth);

	vector<Route> routes = calculateRoutesRecursive(start, end, obstacles);

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

vector<Route> RouterImpl::calculateRoutesRecursive(const Point &start, const Point &end, const vector<Circle> &obstacles) const
{
	vector<Route> result;
	Path endPart(end, end, m_robotWidth);

	if (endPart.intersectsWith(obstacles))
		return result;

	Path directPath(start, end, m_robotWidth);
	vector<Circle> realObstacles;

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
		if (directPath.intersectsWith(*i))
			realObstacles.push_back(*i);

	if (realObstacles.size() == 0)
	{
		Route directRoute(m_robotWidth);
		directRoute.addPoint(start);
		directRoute.addPoint(end);
		result.push_back(directRoute);
		return result;
	}

	double closestDistance = numeric_limits<double>::max();
	Circle closestObstacle;

	for (vector<Circle>::const_iterator i = realObstacles.begin(); i != realObstacles.end(); ++i)
	{
		const Circle &obstacle = *i;
		double distance = obstacle.getDistanceTo(start);

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestObstacle = obstacle;
		}
	}

	vector<Point> pointsBesideObstacle = getPointsBesideObstacle(directPath, closestObstacle);
	for (vector<Point>::const_iterator i = pointsBesideObstacle.begin(); i != pointsBesideObstacle.end(); ++i)
	{
		const Point &pointBesideObstacle = *i;
		vector<Route> startParts = calculateRoutesRecursive(start, pointBesideObstacle, obstacles);
		vector<Route> completeRoutes = calculateRoutesRecursive(startParts, end, obstacles);
		result.insert(result.end(), completeRoutes.begin(), completeRoutes.end());
	}

	return result;
}

vector<Route> RouterImpl::calculateRoutesRecursive(const vector<Route> &startRoutes, const Point &end, const vector<Circle> &obstacles) const
{
	vector<Route> result;

	for (vector<Route>::const_iterator i = startRoutes.begin(); i != startRoutes.end(); ++i)
	{
		const Route &startRoute = *i;
		const Common::Point &start = startRoute.getLastPoint();
		vector<Route> routes = calculateRoutesRecursive(start, end, obstacles);

		for (vector<Route>::const_iterator j = routes.begin(); j != routes.end(); ++j)
		{
			const Route &endRoute = *j;
			Route completeRoute = startRoute;
			completeRoute.add(endRoute);
			result.push_back(completeRoute);
		}
	}

	return result;
}
