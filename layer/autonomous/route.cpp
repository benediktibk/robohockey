#include "layer/autonomous/route.h"
#include "common/path.h"
#include "common/angle.h"
#include "common/robotposition.h"
#include "common/signum.h"
#include <assert.h>
#include <math.h>
#include <algorithm>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

Route::Route() :
	m_width(0)
{ }

Route::Route(double width) :
	m_width(width)
{
	assert(m_width > 0);
}

void Route::addPoint(const Point &point)
{
	m_points.push_back(point);
}

void Route::add(const Route &route)
{
	assert(getLastPoint() == route.getFirstPoint());

	list<Point>::const_iterator begin = route.m_points.begin();
	++begin;
	m_points.insert(m_points.end(), begin, route.m_points.end());
}

size_t Route::getPointCount() const
{
	return m_points.size();
}

bool Route::isValid() const
{
	return getPointCount() >= 1 && m_width > 0;
}

const Point &Route::getLastPoint() const
{
	assert(getPointCount() > 0);
	return m_points.back();
}

const Point &Route::getNextToLastPoint() const
{
	assert(getPointCount() > 1);
	list<Point>::const_reverse_iterator iterator = m_points.rbegin();
	++iterator;
	return *iterator;
}

const Point &Route::getSecondPoint() const
{
	assert(getPointCount() > 1);
	list<Point>::const_iterator iterator = m_points.begin();
	++iterator;
	return *iterator;
}

const Point &Route::getFirstPoint() const
{
	assert(getPointCount() > 0);
	return m_points.front();
}

list<Point> Route::getAllPoints() const
{
	return m_points;
}

void Route::removeFirstPoint()
{
	assert(getPointCount() > 0);
	m_points.pop_front();
}

double Route::getWidth() const
{
	return m_width;
}

bool Route::intersectsWith(const vector<Circle> &objects) const
{
	list<Point>::const_iterator pointsEnd = m_points.end();
	--pointsEnd;

	for(list<Point>::const_iterator k = m_points.begin(); k != pointsEnd; ++k)
	{
		list<Point>::const_iterator nextElement = k;
		++nextElement;
		Path currentPath(*k,*nextElement, m_width);
		for(vector<Circle>::const_iterator i = objects.begin(); i != objects.end(); ++i)
			if(currentPath.intersectsWith(*i))
				return true;
	}

	return false;
}

void Route::replaceFirstPoint(const Point &point)
{
	assert(isValid());
	*(m_points.begin()) = point;
}

double Route::getLength() const
{
	double totalLength = 0;
	list<Point>::const_iterator end = m_points.end();
	--end;

	for (list<Point>::const_iterator i = m_points.begin(); i != end; ++i)
	{
		list<Point>::const_iterator next = i;
		++next;
		const Point &currentPoint = *i;
		const Point &nextPoint = *next;
		totalLength += currentPoint.distanceTo(nextPoint);
	}

	return totalLength;
}

Angle Route::getMaximumBend(const Angle &startOrientation, const Angle &endOrientation) const
{
	assert(isValid());
	const Point &firstPoint = getFirstPoint();
	const Point &secondPoint = getSecondPoint();
	const Point &lastPoint = getLastPoint();
	const Point &nextToLastPoint = getNextToLastPoint();
	Angle startBend = Angle(firstPoint, secondPoint) - startOrientation;
	Angle endBend = endOrientation - Angle(nextToLastPoint, lastPoint);
	startBend.abs();
	endBend.abs();
	Angle maximumBend = startBend;

	if (endBend.getValueBetweenZeroAndTwoPi() > maximumBend.getValueBetweenZeroAndTwoPi())
		maximumBend = endBend;

	list<Point>::const_iterator customEnd = m_points.end();
	--customEnd;
	--customEnd;
	for (list<Point>::const_iterator i = m_points.begin(); i != customEnd; ++i)
	{
		list<Point>::const_iterator next = i;
		++next;
		list<Point>::const_iterator nextTwo = next;
		++nextTwo;
		Angle angle = Angle::getHalfRotation() - Angle(*next, *i, *nextTwo);

		if (angle.getValueBetweenZeroAndTwoPi() > maximumBend.getValueBetweenZeroAndTwoPi())
			maximumBend = angle;
	}

	return maximumBend;
}

void Route::fixRotationOfFinalStep(
		const Angle &finalOrientation, const Angle &maximumRotation,
		double minimumStepAfterMaximumRotation)
{
	assert(isValid());
	RobotPosition end(getLastPoint(), finalOrientation + Angle::getHalfRotation());
	Angle rotation = calculateNecessaryRotation(end, getNextToLastPoint());
	Angle rotationAbsolute = rotation;
	rotationAbsolute.abs();
	reverse(m_points.begin(), m_points.end());
	list<Point>::iterator position = m_points.begin();

	while (rotationAbsolute.getValueBetweenZeroAndTwoPi() > maximumRotation.getValueBetweenZeroAndTwoPi() &&
		   position != m_points.end())
	{
		Point newPoint = calculateMaximumRotatedNextPoint(end, rotation, maximumRotation, minimumStepAfterMaximumRotation);
		++position;
		position = m_points.insert(position, newPoint);
		list<Point>::iterator lastPosition = position;
		--lastPosition;
		list<Point>::iterator nextPosition = position;
		++nextPosition;
		end = RobotPosition(*position, Angle(*lastPosition, *position));
		rotation = calculateNecessaryRotation(end, *nextPosition);
		rotationAbsolute = rotation;
		rotationAbsolute.abs();
	}

	reverse(m_points.begin(), m_points.end());
}

Angle Route::calculateNecessaryRotation(const RobotPosition &start, const Point &end)
{
	Angle angleBetweenStartAndEnd(start.getPosition(), end);
	return angleBetweenStartAndEnd - start.getOrientation();
}

Point Route::calculateMaximumRotatedNextPoint(
		const RobotPosition &start, const Angle &desiredRotation,
		const Angle &maximumRotation, double minimumStepAfterMaximumRotation)
{
	int rotationSign = sgn(desiredRotation.getValueBetweenMinusPiAndPi());
	Angle possibleRotation = maximumRotation.getValueBetweenZeroAndTwoPi()*rotationSign;
	Angle totalRotation = start.getOrientation() + possibleRotation;
	Point modifiedEnd(minimumStepAfterMaximumRotation, 0);
	modifiedEnd.rotate(totalRotation);
	modifiedEnd = start.getPosition() + modifiedEnd;
	return modifiedEnd;
}
