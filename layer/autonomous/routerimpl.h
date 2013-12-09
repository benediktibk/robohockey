#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERIMPL_H

#include "layer/autonomous/router.h"
#include <vector>

namespace RoboHockey
{
namespace Common
{
	class Point;
	class Circle;
	class Path;
}

namespace Layer
{
namespace Autonomous
{
	class Route;

	class RouterImpl :
			public Router
	{
	public:
		RouterImpl(double robotWidth);

		virtual Route calculateRoute(const Common::Point &start, const Common::Point &end, const Field &field) const;
		std::vector<Common::Point> getPointsBesideObstacle(const Common::Path &path, const Common::Circle &obstacle) const;

	private:
		std::vector<Route> calculateRoutesRecursive(const Common::Point &start, const Common::Point &end, const std::vector<Common::Circle> &obstacles) const;
		std::vector<Route> calculateRoutesRecursive(const std::vector<Route> &startRoutes, const Common::Point &end, const std::vector<Common::Circle> &obstacles) const;

	private:
		double m_robotWidth;
	};
}
}
}

#endif
