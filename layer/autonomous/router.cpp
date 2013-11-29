#include "layer/autonomous/router.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/route.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

Router::Router(double robotWidth, const Field &field) :
	m_field(field),
	m_robotWidth(robotWidth)
{ }

Route Router::calculateRoute(const Point &/*start*/, const Point &end) const
{
	vector<Circle> obstacles = m_field.getAllObstacles();
	Route route(m_robotWidth);
	route.addPoint(end);

	if (route.intersectsWith(obstacles))
		return Route(m_robotWidth);
	else
		return route;
}

vector<Point> Router::getPointsBesideObstacle(
		const vector<Point> &/*intersectionPointsWithObstacle*/, const Circle &/*obstacle*/) const
{
	return vector<Point>();
}
