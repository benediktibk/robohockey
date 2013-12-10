#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTER_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTER_H

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
}

namespace Layer
{
namespace Autonomous
{
	class Route;
	class Field;

	class Router
	{
	public:
		virtual ~Router() { }

		virtual Route calculateRoute(const Common::RobotPosition &start, const Common::RobotPosition &end, const Field &field) const = 0;
	};
}
}
}

#endif


