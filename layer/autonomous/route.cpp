#include "layer/autonomous/route.h"
#include "common/path.h"
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

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
	return getPointCount() >= 1;
}

const Point &Route::getLastPoint() const
{
	assert(getPointCount() > 0);
	return m_points.back();
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
