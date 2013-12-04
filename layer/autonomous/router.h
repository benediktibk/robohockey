#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTER_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTER_H

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
	class Field;
	class Route;

	class Router
	{
	public:
		Router(double robotWidth, const Field &field);

		Route calculateRoute(const Common::Point &start, const Common::Point &end) const;
		std::vector<Common::Point> getPointsBesideObstacle(const Common::Path &path, const Common::Circle &obstacle) const;

	private:
		const Field &m_field;
		double m_robotWidth;
	};
}
}
}

#endif
