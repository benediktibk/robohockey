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
	for(list<Point>::const_iterator k = m_points.begin(); k != m_points.end(); ++k)
	{
		Path currentPath(*k,*k++, m_width);
		for(vector<Circle>::const_iterator i = objects.begin(); i != objects.end(); ++i)
		{
			if(currentPath.intersectsWith(*i))
				return true;
		}
	}
	return false;
}
