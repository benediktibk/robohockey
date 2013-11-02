#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOT_H

namespace RoboHockey
{
namespace Common
{
	class Point;
}

namespace Layer
{
namespace Autonomous
{
	class Robot
	{
	public:
		virtual ~Robot() { }

		virtual void goTo(const Common::Point &position) = 0;
	};
}
}
}

#endif
