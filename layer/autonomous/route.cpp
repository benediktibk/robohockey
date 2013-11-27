#include "layer/autonomous/route.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

Route::Route()
{ }

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
	return getPointCount() > 0;
}
