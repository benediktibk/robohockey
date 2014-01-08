#include "layer/autonomous/routerimpl.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/route.h"
#include "layer/autonomous/routelengthcompare.h"
#include "layer/autonomous/routingobstacle.h"
#include "layer/autonomous/routingresult.h"
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
	m_maximumSearchDepth(7),
	m_robotWidth(robotWidth)
{ }

Route RouterImpl::calculateRoute(
		const RobotPosition &start, const RobotPosition &end, const FieldPositionChecker &field,
		const Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool ignoreFinalOrientation,
		const vector<Circle> &hardObstacles, const vector<Circle> &softObstacles) const
{
	if (!field.isPointInsideField(end.getPosition()))
		return Route();

	Circle endCircle(end.getPosition(), sqrt(2)*m_robotWidth);
	if (	endCircle.overlapsWith(hardObstacles) ||
			endCircle.overlapsWith(softObstacles))
		return Route();

	const Point &startPosition = start.getPosition();
	const Point &endPosition = end.getPosition();
	const Angle &startOrientation = start.getOrientation();
	const Angle &endOrientation = end.getOrientation();
	vector<Circle> allObstacles = filterObstacles(softObstacles, hardObstacles, startPosition);

	bool startInsideField = field.isPointInsideField(startPosition);
	list<RoutingObstacle> consideredObstacles;
	vector<RoutingResult> routingResults = calculateStartParts(
				start, endPosition, field, allObstacles, 0, consideredObstacles,
				maximumRotation, minimumStepAfterMaximumRotation, startInsideField);
	vector<Route> routes = fixRotationOfFinalStep(
				routingResults, startOrientation, endOrientation, maximumRotation,
				minimumStepAfterMaximumRotation, allObstacles, ignoreFinalOrientation);

	if (routes.size() == 0)
		return Route();
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
	double offsetDistanceLongPoint = 0.51*sqrt(2)*m_robotWidth + obstacle.getDiameter()/2;
	Angle offsetAngleShortPoint = path.getAngleBetweenStartAndEnd();

	if((intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromStart) ||
		(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromEnd))
		return pointsBesideObstacle;

	if(intersectionPoints.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeNoIntersect)
	{
		Point centerBetweenIntersectPoints = (intersectionPoints.front() + intersectionPoints.back())/2;
		offsetDistanceLongPoint -= centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		double offsetDistanceShortPoint = offsetDistanceLongPoint;
		Line line(path.getCenterLine());
		line.shiftParallel(intersectionPoints.front());

		if(!path.isCircleCenterOnPath(obstacle))
			offsetDistanceLongPoint += 2*centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		else
			offsetDistanceShortPoint += 2*centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		if(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromLeft)
		{
			offsetAngleShortPoint = offsetAngleShortPoint + Angle::getThreeQuarterRotation();
			if(line.isTargetPointRightOfLine(obstacle.getCenter()) && !path.isCircleCenterOnPath(obstacle))
				offsetAngleShortPoint = offsetAngleShortPoint - Angle::getHalfRotation();
		}
		else
		{
			offsetAngleShortPoint = offsetAngleShortPoint + Angle::getQuarterRotation();
			if(!line.isTargetPointRightOfLine(obstacle.getCenter()) && !path.isCircleCenterOnPath(obstacle))
				offsetAngleShortPoint = offsetAngleShortPoint - Angle::getHalfRotation();
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

vector<Circle> RouterImpl::filterObstacles(
		const vector<Circle> &softObstacles,
		const vector<Circle> &hardObstacles,
		const Point &position) const
{
	vector<Circle> allObstacles;
	allObstacles.reserve(hardObstacles.size() + softObstacles.size());
	Circle startCircle(position, sqrt(2)*m_robotWidth);

	for (vector<Circle>::const_iterator i = hardObstacles.begin(); i != hardObstacles.end(); ++i)
	{
		Circle obstacle = *i;
		const Point &center = obstacle.getCenter();

		if (startCircle.isInside(center))
			continue;

		if (startCircle.overlapsWith(obstacle))
		{
			double distanceToCenter = startCircle.getDistanceTo(center);
			double diameter = distanceToCenter*2*0.99;
			obstacle.setDiameter(diameter);
		}

		allObstacles.push_back(obstacle);
	}

	for (vector<Circle>::const_iterator i = softObstacles.begin(); i != softObstacles.end(); ++i)
	{
		const Circle &obstacle = *i;

		if (!startCircle.overlapsWith(obstacle))
			allObstacles.push_back(obstacle);
	}

	return allObstacles;
}

vector<RoutingResult> RouterImpl::calculateStartParts(
		const RobotPosition &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const list<RoutingObstacle> &consideredObstacles,
		const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation,
		bool startInsideField) const
{
	++searchDepth;
	if (searchDepth > m_maximumSearchDepth)
		return vector<RoutingResult>();

	Circle endCircle(end, sqrt(2)*m_robotWidth);
	bool endCovered = endCircle.overlapsWith(obstacles);
	if (endCovered)
		return calculateStartPartsWithCoveredEnd(
				start, end, field, obstacles, searchDepth, consideredObstacles,
				maximumRotation, minimumStepAfterMaximumRotation, startInsideField);
	else
		return calculateStartPartsWithFreeEnd(
				start, end, field, obstacles, searchDepth, consideredObstacles,
				maximumRotation, minimumStepAfterMaximumRotation, startInsideField);
}

vector<RoutingResult> RouterImpl::calculateStartPartsWithFreeEnd(
		const RobotPosition &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const list<RoutingObstacle> &consideredObstacles,
		const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation,
		bool startInsideField) const
{
	const Point &startPoint = start.getPosition();
	Path directPath(startPoint, end, m_robotWidth);
	vector<Circle> realObstacles = findRealObstacles(obstacles, directPath);

	if (realObstacles.size() == 0)
		return calculateStartPartsWithFreeDirectPath(
					start, end, field, obstacles, searchDepth, consideredObstacles,
					maximumRotation, minimumStepAfterMaximumRotation, startInsideField);
	else
	{
		Circle closestObstacle = findClosestObstacle(realObstacles, startPoint);
		vector<RoutingResult> startParts = calculateRoutesToPointsBesideObstacle(
					closestObstacle, start, end, field, obstacles,
					searchDepth, consideredObstacles, maximumRotation, minimumStepAfterMaximumRotation, startInsideField);
		return calculateEndParts(
					startParts, end, field, obstacles, searchDepth, maximumRotation, minimumStepAfterMaximumRotation);
	}
}

vector<RoutingResult> RouterImpl::calculateStartPartsWithCoveredEnd(
		const RobotPosition &start, const Point &end, const FieldPositionChecker &field, const vector<Circle> &obstacles,
		unsigned int searchDepth, const list<RoutingObstacle> &consideredObstacles,
		const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation,
		bool startInsideField) const
{
	const Point &startPoint = start.getPosition();
	Path path(startPoint, end, m_robotWidth);
	vector<Circle> obstaclesTillEnd = findRealObstacles(obstacles, path);

	if (obstaclesTillEnd.size() == 0)
	{
		return calculateStartPartsWithFreeDirectPath(
					start, end, field, obstacles, searchDepth, consideredObstacles,
					maximumRotation, minimumStepAfterMaximumRotation, startInsideField);
	}
	else
	{
		Circle obstacle = findClosestObstacle(obstaclesTillEnd, startPoint);
		double diameter = obstacle.getDiameter();
		Point direction = end - startPoint;
		double directionLength = startPoint.distanceTo(end);
		double desiredLength = directionLength + 2*diameter;
		Point directionModified = direction/directionLength*desiredLength;
		Point extendedEnd = startPoint + directionModified;
		return calculateRoutesToPointsBesideObstacle(
					obstacle, start, extendedEnd, field, obstacles,
					searchDepth, consideredObstacles, maximumRotation,
					minimumStepAfterMaximumRotation, startInsideField);
	}
}

vector<RoutingResult> RouterImpl::calculateStartPartsWithFreeDirectPath(
		const RobotPosition &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const list<RoutingObstacle> &consideredObstacles, const Angle &maximumRotation,
		double minimumStepAfterMaximumRotation, bool startInsideField) const
{
	Angle rotation = Route::calculateNecessaryRotation(start, end);
	Angle rotationAbsolute = rotation;
	rotationAbsolute.abs();
	Compare compare(0.001);

	if (compare.isFuzzySmaller(rotationAbsolute.getValueBetweenZeroAndTwoPi(), maximumRotation.getValueBetweenZeroAndTwoPi()))
	{
		vector<RoutingResult> result;
		Route directRoute(m_robotWidth);
		directRoute.addPoint(start.getPosition());
		directRoute.addPoint(end);
		result.push_back(RoutingResult(directRoute, consideredObstacles));
		return result;
	}
	else
	{
		Point modifiedEnd = Route::calculateMaximumRotatedNextPoint(
					start, rotation, maximumRotation, minimumStepAfterMaximumRotation);
		bool modifiedEndInsideField = field.isPointInsideField(modifiedEnd);

		if (!modifiedEndInsideField && startInsideField)
			return vector<RoutingResult>();

		vector<RoutingResult> startParts = calculateStartParts(
					start, modifiedEnd, field, obstacles, searchDepth, consideredObstacles,
					maximumRotation, minimumStepAfterMaximumRotation, startInsideField);
		return calculateEndParts(
					startParts, end, field, obstacles, searchDepth,
					maximumRotation, minimumStepAfterMaximumRotation);
	}
}

vector<RoutingResult> RouterImpl::calculateEndParts(
		const vector<RoutingResult> &startRoutes, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation) const
{
	vector<RoutingResult> result;
	result.reserve(startRoutes.size());

	for (vector<RoutingResult>::const_iterator i = startRoutes.begin(); i != startRoutes.end(); ++i)
	{
		const Route &startRoute = i->getRoute();
		const list<RoutingObstacle> &consideredObstacles = i->getObstacles();
		const Common::Point &lastPoint = startRoute.getLastPoint();
		const Common::Point &nextToLastPoint = startRoute.getNextToLastPoint();
		RobotPosition start(lastPoint, Angle(nextToLastPoint, lastPoint));
		bool startInsideField = field.isPointInsideField(lastPoint);
		assert(!(lastPoint == end));

		list<RoutingObstacle> reducedConsideredObstacles;
		if (consideredObstacles.size() > 0)
			reducedConsideredObstacles.push_back(consideredObstacles.back());
		vector<RoutingResult> routes = calculateStartParts(
					start, end, field, obstacles, searchDepth, reducedConsideredObstacles,
					maximumRotation, minimumStepAfterMaximumRotation, startInsideField);

		for (vector<RoutingResult>::const_iterator j = routes.begin(); j != routes.end(); ++j)
		{
			const Route &endRoute = j->getRoute();
			const list<RoutingObstacle> &endObstacles = j->getObstacles();
			Route completeRoute = startRoute;
			completeRoute.add(endRoute);
			result.push_back(RoutingResult(completeRoute, endObstacles));
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

vector<RoutingResult> RouterImpl::calculateRoutesToPointsBesideObstacle(
		const Circle &obstacle, const RobotPosition &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const list<RoutingObstacle> &consideredObstacles, const Common::Angle &maximumRotation,
		double minimumStepAfterMaximumRotation, bool startIsInsideField) const
{
	Point startPoint = start.getPosition();
	Path path(startPoint, end, m_robotWidth);
	vector<Point> pointsBesideObstacle = getPointsBesideObstacle(path, obstacle);
	vector<RoutingResult> result;

	if(pointsBesideObstacle.size() != 2)
		return result;

	Line line(startPoint, end);
	assert(line.isOnePointLeftAndOneRightOfLine(pointsBesideObstacle[0], pointsBesideObstacle[1]));
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

	bool rightPointInsideField = field.isPointInsideField(rightPoint);
	if ((rightPointInsideField && startIsInsideField) || !startIsInsideField)
	{
		list<RoutingObstacle> extendedConsideredObstacles = consideredObstacles;
		extendedConsideredObstacles.push_back(RoutingObstacle(obstacle, true));

		if (!detectLoopInConsideredObstacles(extendedConsideredObstacles))
		{
			vector<RoutingResult> startParts = calculateStartParts(
						start, rightPoint, field, obstacles, searchDepth, extendedConsideredObstacles,
						maximumRotation, minimumStepAfterMaximumRotation, rightPointInsideField);
			result.insert(result.end(), startParts.begin(), startParts.end());
		}
	}

	bool leftPointInsideField = field.isPointInsideField(leftPoint);
	if ((leftPointInsideField && startIsInsideField) || !startIsInsideField)
	{
		list<RoutingObstacle> extendedConsideredObstacles = consideredObstacles;
		extendedConsideredObstacles.push_back(RoutingObstacle(obstacle, false));

		if (!detectLoopInConsideredObstacles(extendedConsideredObstacles))
		{
			vector<RoutingResult> startParts = calculateStartParts(
						start, leftPoint, field, obstacles, searchDepth, extendedConsideredObstacles,
						maximumRotation, minimumStepAfterMaximumRotation, leftPointInsideField);
			result.insert(result.end(), startParts.begin(), startParts.end());
		}
	}

	return result;
}

vector<Route> RouterImpl::fixRotationOfFinalStep(
		const vector<RoutingResult> &routes, const Angle &startOrientation, const Angle &finalOrientation,
		const Angle &maximumRotation, double minimumStepAfterMaximumRotation,
		const std::vector<Circle> &obstacles, bool ignoreFinalOrientation) const
{
	vector<Route> result;
	result.reserve(routes.size());

	for (vector<RoutingResult>::const_iterator i = routes.begin(); i != routes.end(); ++i)
	{
		Route route = i->getRoute();

		if (!ignoreFinalOrientation)
		{
			route.fixRotationOfFinalStep(finalOrientation, maximumRotation, minimumStepAfterMaximumRotation);

			if (!route.isValid())
				continue;

			if (route.intersectsWith(obstacles))
				continue;

			Angle maximumBend = route.getMaximumBend(startOrientation, finalOrientation);
			maximumBend.abs();
			if (maximumBend.getValueBetweenZeroAndTwoPi() > maximumRotation.getValueBetweenZeroAndTwoPi())
				continue;
		}

		result.push_back(route);
	}

	return result;
}

bool RouterImpl::detectLoopInConsideredObstacles(const list<RoutingObstacle> &obstacles) const
{
	if (obstacles.size() == 0)
		return false;

	const RoutingObstacle &lastObstacle = obstacles.back();
	size_t distance = 0;
	bool found = false;
	list<RoutingObstacle>::const_reverse_iterator i = obstacles.rbegin();
	++i;
	for (; i != obstacles.rend() && !found; ++i)
	{
		++distance;
		if (lastObstacle.getObstacle() == i->getObstacle())
		{
			if (i->wentRightBeside() != lastObstacle.wentRightBeside())
				return true;
			else
				found = true;
		}
	}

	if (found)
		return distance > 1;
	else
		return false;
}
