#include "layer/autonomous/routingobstacle.h"
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

RoutingObstacle::RoutingObstacle() :
	m_valid(false)
{ }

RoutingObstacle::RoutingObstacle(const Circle &obstacle, bool wentRightBeside) :
	m_obstacle(obstacle),
	m_wentRightBeside(wentRightBeside),
	m_valid(true)
{ }

bool RoutingObstacle::isValid() const
{
	return m_valid;
}

bool RoutingObstacle::wentRightBeside() const
{
	assert(isValid());
	return m_wentRightBeside;
}

const Circle &RoutingObstacle::getObstacle() const
{
	assert(isValid());
	return m_obstacle;
}

bool RoutingObstacle::operator==(const RoutingObstacle &routingObstacle) const
{
	return	getObstacle() == routingObstacle.getObstacle() &&
			wentRightBeside() == routingObstacle.wentRightBeside();
}

