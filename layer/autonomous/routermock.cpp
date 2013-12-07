#include "layer/autonomous/routermock.h"
#include "layer/autonomous/route.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

Route RouterMock::calculateRoute(const Point &start, const Point &end, const Field &) const
{
	Route route(0.38);
	route.addPoint(start);
	route.addPoint(end);
	return route;
}
