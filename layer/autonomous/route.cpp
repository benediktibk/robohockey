#include "layer/autonomous/route.h"
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

double Route::getWidth() const
{
	return m_width;
}

bool Route::intersectsWith(const std::vector<Common::Circle> &/*objects*/) const
{
	return false;
}
