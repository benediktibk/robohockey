#include "layer/autonomous/routingresult.h"

using namespace std;
using namespace RoboHockey::Layer::Autonomous;

RoutingResult::RoutingResult()
{ }

RoutingResult::RoutingResult(const Route &route, const list<RoutingObstacle> &obstacles) :
	m_route(route),
	m_obstacles(obstacles)
{ }

bool RoutingResult::isValid() const
{
	return m_route.isValid();
}

const Route &RoutingResult::getRoute() const
{
	return m_route;
}

const list<RoutingObstacle> &RoutingResult::getObstacles() const
{
	return m_obstacles;
}

