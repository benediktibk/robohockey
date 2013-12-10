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
		std::vector<Route> calculateStartParts(
				const Common::Point &start, const Common::Point &end, const Field &field,
				const std::vector<Common::Circle> &obstacles, unsigned int searchDepth) const;
		std::vector<Route> calculateEndParts(
				const std::vector<Route> &startRoutes, const Common::Point &end, const Field &field,
				const std::vector<Common::Circle> &obstacles, unsigned int searchDepth) const;
		std::vector<Common::Circle> findRealObstacles(const std::vector<Common::Circle> &obstacles, const Common::Path &path) const;
		Common::Circle findClosestObstacle(const std::vector<Common::Circle> &obstacles, const Common::Point &point) const;

	private:
		const unsigned int m_maximumSearchDepth;
		double m_robotWidth;
	};
}
}
}

#endif
