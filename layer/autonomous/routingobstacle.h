#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTINGOBSTACLE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTINGOBSTACLE_H

#include "common/circle.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RoutingObstacle
	{
	public:
		RoutingObstacle();
		RoutingObstacle(const Common::Circle &obstacle, bool wentRightBeside);

		bool isValid() const;
		bool wentRightBeside() const;
		const Common::Circle& getObstacle() const;

		bool operator==(const RoutingObstacle &routingObstacle) const;

	private:
		Common::Circle m_obstacle;
		bool m_wentRightBeside;
		bool m_valid;
	};
}
}
}

#endif


