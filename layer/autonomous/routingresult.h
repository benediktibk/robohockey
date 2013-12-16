#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTINGRESULT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTINGRESULT_H

#include <list>
#include "layer/autonomous/routingobstacle.h"
#include "layer/autonomous/route.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RoutingResult
	{
	public:
		RoutingResult();
		RoutingResult(const Route &route, const std::list<RoutingObstacle> &obstacles);

		bool isValid() const;
		const Route& getRoute() const;
		const std::list<RoutingObstacle>& getObstacles() const;

	private:
		Route m_route;
		std::list<RoutingObstacle> m_obstacles;

	};
}
}
}

#endif


