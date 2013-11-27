#include "common/path.h"
#include "common/circle.h"

using namespace RoboHockey::Common;

Path::Path(const Point &start, const Point &end, double width) :
	m_start(start),
	m_end(end),
	m_width(width)
{ }

bool Path::intersectsWith(const Circle &/*circle*/) const
{
	return false;
}
