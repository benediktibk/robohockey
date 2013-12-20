#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERIMPL_H

#include "layer/autonomous/router.h"
#include <vector>
#include <list>

namespace RoboHockey
{
namespace Common
{
	class Point;
	class Circle;
	class Path;
	class RobotPosition;
}

namespace Layer
{
namespace Autonomous
{
	class RoutingResult;
	class RoutingObstacle;

	class RouterImpl :
			public Router
	{
	public:
		RouterImpl(double robotWidth);

		virtual Route calculateRoute(
				const Common::RobotPosition &start, const Common::RobotPosition &end, const Field &field,
				const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation,
				bool ignoreSoftObstacles, bool ignoreFinalOrientation) const;
		std::vector<Common::Point> getPointsBesideObstacle(const Common::Path &path, const Common::Circle &obstacle) const;
		std::vector<Common::Circle> filterObstacles(const std::vector<Common::Circle> &softObstacles,
				const std::vector<Common::Circle> &hardObstacles, const Common::Point &position) const;
		bool detectLoopInConsideredObstacles(const std::list<RoutingObstacle> &obstacles) const;

	private:
		std::vector<RoutingResult> calculateStartParts(const Common::RobotPosition &start, const Common::Point &end, const Field &field,
				const std::vector<Common::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, const Common::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithFreeEnd(
				const Common::RobotPosition &start, const Common::Point &end, const Field &field,
				const std::vector<Common::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, const Common::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithCoveredEnd(
				const Common::RobotPosition &start, const Common::Point &end, const Field &field,
				const std::vector<Common::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, const Common::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithFreeDirectPath(
				const Common::RobotPosition &start, const Common::Point &end, const Field &field,
				const std::vector<Common::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles,
				const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateEndParts(
				const std::vector<RoutingResult> &startRoutes, const Common::Point &end, const Field &field,
				const std::vector<Common::Circle> &obstacles, unsigned int searchDepth, const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation) const;
		std::vector<Common::Circle> findRealObstacles(const std::vector<Common::Circle> &obstacles, const Common::Path &path) const;
		Common::Circle findClosestObstacle(const std::vector<Common::Circle> &obstacles, const Common::Point &point) const;
		std::vector<RoutingResult> calculateRoutesToPointsBesideObstacle(
				const Common::Circle &obstacle, const Common::RobotPosition &start, const Common::Point &end,
				const Field &field, const std::vector<Common::Circle> &obstacles,
				unsigned int searchDepth, const std::list<RoutingObstacle> &consideredObstacles,
				const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool startIsInsideField) const;
		std::vector<Route> fixRotationOfFinalStep(
				const std::vector<RoutingResult> &routes, const Common::Angle &startOrientation,
				const Common::Angle &finalOrientation, const Common::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation,	const std::vector<Common::Circle> &obstacles,
				bool ignoreFinalOrientation) const;

	private:
		const unsigned int m_maximumSearchDepth;
		double m_robotWidth;
	};
}
}
}

#endif
