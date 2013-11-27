#include "layer/autonomous/router.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/route.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

Router::Router(double robotWidth, const Field &field) :
	m_field(field),
	m_robotWidth(robotWidth)
{ }

Route Router::calculateRoute(const Point &/*start*/, const Point &end) const
{
	Route route(m_robotWidth);
	route.addPoint(end);
	return route;
}
