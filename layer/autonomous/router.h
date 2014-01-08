#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTER_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTER_H

#include <vector>

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
	class Circle;
	class Point;
	class Angle;
}

namespace Layer
{
namespace Autonomous
{
	class Route;
	class FieldPositionChecker;

	class Router
	{
	public:
		virtual ~Router() { }

		virtual Route calculateRoute(
				const Common::RobotPosition &start, const Common::RobotPosition &end, const FieldPositionChecker &field,
				const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool ignoreFinalOrientation,
				const std::vector<Common::Circle> &hardObstacles, const std::vector<Common::Circle> &softObstacles) const = 0;
		virtual std::vector<Common::Circle> filterObstacles(const std::vector<Common::Circle> &softObstacles,
				const std::vector<Common::Circle> &hardObstacles, const Common::Point &position) const = 0;
	};
}
}
}

#endif


