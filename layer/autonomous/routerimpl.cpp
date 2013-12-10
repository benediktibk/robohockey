#include "layer/autonomous/routerimpl.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/route.h"
#include "layer/autonomous/routelengthcompare.h"
#include "common/path.h"
#include "common/pathintersectpoints.h"
#include "common/angle.h"
#include "common/line.h"
#include "common/robotposition.h"
#include "common/compare.h"
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <limits>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

RouterImpl::RouterImpl(double robotWidth) :
	m_maximumSearchDepth(15),
	m_robotWidth(robotWidth)
{ }

Route RouterImpl::calculateRoute(const RobotPosition &start, const RobotPosition &end, const Field &field) const
{
	const vector<Circle> obstacles = field.getAllObstacles();

	Path startPart(start.getPosition(), start.getPosition(), m_robotWidth);
	if (startPart.intersectsWith(obstacles))
		return Route(m_robotWidth);

	Path endPart(end.getPosition(), end.getPosition(), m_robotWidth);
	if (endPart.intersectsWith(obstacles))
		return Route(m_robotWidth);

	const Point &startPosition = start.getPosition();
	const Point &endPosition = end.getPosition();
	vector<Route> routes = calculateStartParts(startPosition, endPosition, field, obstacles, 0, true, true);

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
	Point longPointBesideObstacle;
	double offsetDistanceLongPoint = sqrt(2)*0.5*(m_robotWidth + obstacle.getDiameter()) + 0.5*m_robotWidth;
	Angle offsetAngleShortPoint = path.getAgnleBetweenStartAndEnd();

	assert(intersectionPoints.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeFromStart);
	assert(intersectionPoints.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeFromEnd);

	if(intersectionPoints.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeNoIntersect)
	{
		Point centerBetweenIntersectPoints = (intersectionPoints.front() + intersectionPoints.back())/2;
		double offsetDistanceShortPoint = 0.5*m_robotWidth + centerBetweenIntersectPoints.distanceTo(intersectionPoints.front());;

		if(!path.isCircleCenterOnPath(obstacle))
			offsetDistanceLongPoint += centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		else
		{
			offsetDistanceShortPoint += 2*centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
			offsetDistanceLongPoint -= centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		}
		if(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromLeft)
		{
			offsetAngleShortPoint = offsetAngleShortPoint + Angle::getThreeQuarterRotation();
			if(Line(intersectionPoints.front(), intersectionPoints.back()).isTargetPointRightOfLine(obstacle.getCenter()) && !path.isCircleCenterOnPath(obstacle))
				offsetAngleShortPoint = offsetAngleShortPoint- Angle::getHalfRotation();
		}
		else
		{
			offsetAngleShortPoint = offsetAngleShortPoint + Angle::getQuarterRotation();
			if(!Line(intersectionPoints.front(), intersectionPoints.back()).isTargetPointRightOfLine(obstacle.getCenter()) && !path.isCircleCenterOnPath(obstacle))
				offsetAngleShortPoint = offsetAngleShortPoint- Angle::getHalfRotation();
		}

		shortPointBesideObstacle = centerBetweenIntersectPoints + Point(offsetDistanceShortPoint, offsetAngleShortPoint);
		longPointBesideObstacle = centerBetweenIntersectPoints + Point(offsetDistanceLongPoint, offsetAngleShortPoint + Angle::getHalfRotation());
	}
	else
	{
		shortPointBesideObstacle = obstacle.getCenter() + Point(offsetDistanceLongPoint, offsetAngleShortPoint + Angle::getQuarterRotation());
		longPointBesideObstacle = obstacle.getCenter() + Point(offsetDistanceLongPoint, offsetAngleShortPoint + Angle::getThreeQuarterRotation());
	}

	pointsBesideObstacle.push_back(shortPointBesideObstacle);
	pointsBesideObstacle.push_back(longPointBesideObstacle);
	return pointsBesideObstacle;
}

vector<Route> RouterImpl::calculateStartParts(
		const Point &start, const Point &end, const Field &field,
		const vector<Circle> &obstacles, unsigned int searchDepth, bool canGoLeft, bool canGoRight) const
{
	++searchDepth;
	if (searchDepth > m_maximumSearchDepth)
		return vector<Route>();

	Path endPart(end, end, m_robotWidth);
	bool endCovered = endPart.intersectsWith(obstacles);
	if (endCovered)
		return calculateStartPartsWithCoveredEnd(
				start, end, field, obstacles, searchDepth, canGoLeft, canGoRight);
	else
		return calculateStartPartsWithFreeEnd(
				start, end, field, obstacles, searchDepth, canGoLeft, canGoRight);
}

vector<Route> RouterImpl::calculateStartPartsWithFreeEnd(
		const Point &start, const Point &end, const Field &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		bool canGoLeft, bool canGoRight) const
{
	Path directPath(start, end, m_robotWidth);
	vector<Circle> realObstacles = findRealObstacles(obstacles, directPath);

	if (realObstacles.size() == 0)
	{
		vector<Route> result;
		Route directRoute(m_robotWidth);
		directRoute.addPoint(start);
		directRoute.addPoint(end);
		result.push_back(directRoute);
		return result;
	}

	Circle closestObstacle = findClosestObstacle(realObstacles, start);
	vector<Route> startParts = calculateRoutesToPointsBesideObstacle(
				closestObstacle, start, end, field, obstacles, canGoLeft, canGoRight,
				searchDepth);
	return calculateEndParts(startParts, end, field, obstacles, searchDepth);
}

vector<Route> RouterImpl::calculateStartPartsWithCoveredEnd(
		const Point &start, const Point &end, const Field &field, const vector<Circle> &obstacles,
		unsigned int searchDepth, bool canGoLeft, bool canGoRight) const
{
	Path path(end, end, m_robotWidth);
	vector<Circle> obstaclesAtEnd = findRealObstacles(obstacles, path);
	assert(obstaclesAtEnd.size() > 0);

	if (obstaclesAtEnd.size() > 1)
		return vector<Route>();

	const Circle &obstacle = obstaclesAtEnd.front();
	double diameter = obstacle.getDiameter();
	Point direction = end - start;
	double directionLength = start.distanceTo(end);
	double desiredLength = directionLength + 2*diameter;
	Point directionModified = direction/directionLength*desiredLength;
	Point extendedEnd = start + directionModified;
	vector<Route> startParts = calculateRoutesToPointsBesideObstacle(
				obstacle, start, extendedEnd, field, obstacles, canGoLeft, canGoRight,
				searchDepth);
	return calculateEndParts(startParts, end, field, obstacles, searchDepth);
}

vector<Route> RouterImpl::calculateEndParts(
		const vector<Route> &startRoutes, const Point &end, const Field &field,
		const vector<Circle> &obstacles, unsigned int searchDepth) const
{
	Compare compare(0.01);
	vector<Route> result;
	result.reserve(startRoutes.size());

	for (vector<Route>::const_iterator i = startRoutes.begin(); i != startRoutes.end(); ++i)
	{
		const Route &startRoute = *i;
		const Common::Point &start = startRoute.getLastPoint();

		if (compare.isFuzzyEqual(start, end))
			result.push_back(startRoute);
		else
		{
			vector<Route> routes = calculateStartParts(start, end, field, obstacles, searchDepth, true, true);

			for (vector<Route>::const_iterator j = routes.begin(); j != routes.end(); ++j)
			{
				const Route &endRoute = *j;
				Route completeRoute = startRoute;
				completeRoute.add(endRoute);
				result.push_back(completeRoute);
			}
		}
	}

	return result;
}

vector<Circle> RouterImpl::findRealObstacles(const vector<Circle> &obstacles, const Path &path) const
{
	vector<Circle> result;

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
		if (path.intersectsWith(*i))
			result.push_back(*i);

	return result;
}

Circle RouterImpl::findClosestObstacle(const vector<Circle> &obstacles, const Point &point) const
{
	assert(obstacles.size() > 0);

	double closestDistance = numeric_limits<double>::max();
	Circle closestObstacle;

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		const Circle &obstacle = *i;
		double distance = obstacle.getDistanceTo(point);

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestObstacle = obstacle;
		}
	}

	return closestObstacle;
}

vector<Route> RouterImpl::calculateRoutesToPointsBesideObstacle(
		const Circle &obstacle, const Point &start, const Point &end, const Field &field,
		const vector<Circle> &obstacles, bool canGoLeft, bool canGoRight, unsigned int searchDepth) const
{
	Path path(start, end, m_robotWidth);
	vector<Point> pointsBesideObstacle = getPointsBesideObstacle(path, obstacle);
	assert(pointsBesideObstacle.size() == 2);
	Line line(start, end);
	Point leftPoint;
	Point rightPoint;

	if (line.isTargetPointRightOfLine(pointsBesideObstacle.front()))
	{
		rightPoint = pointsBesideObstacle.front();
		leftPoint = pointsBesideObstacle.back();
	}
	else
	{
		rightPoint = pointsBesideObstacle.back();
		leftPoint = pointsBesideObstacle.front();
	}

	vector<Route> result;
	if (canGoRight && field.isPointInsideField(rightPoint))
	{
		vector<Route> startParts = calculateStartParts(
					start, rightPoint, field, obstacles, searchDepth, false, true);
		result.insert(result.end(), startParts.begin(), startParts.end());
	}

	if (canGoLeft && field.isPointInsideField(leftPoint))
	{
		vector<Route> startParts = calculateStartParts(
					start, leftPoint, field, obstacles, searchDepth, true, false);
		result.insert(result.end(), startParts.begin(), startParts.end());
	}

	return result;
}
