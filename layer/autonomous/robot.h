#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOT_H

#include "layer/autonomous/fieldobject.h"
#include <vector>

namespace RoboHockey
{
namespace Common
{
	class Point;
	class RobotPosition;
}

namespace Layer
{
namespace Autonomous
{
	class Field;

	class Robot
	{
	public:
		virtual ~Robot() { }

		virtual void goTo(const Common::Point &position) = 0;
		virtual void turnTo(const Common::Point &position) = 0;
		virtual bool stuckAtObstacle() = 0;
		virtual bool reachedTarget() = 0;
		virtual void updateActuators(const Field &field) = 0;
		virtual void updateSensorData() = 0;
		virtual void stop() = 0;
		virtual void collectPuckInFront() = 0;
		virtual void leaveCollectedPuck() = 0;
		virtual bool isMoving() = 0;
		virtual void turnAround() = 0;
		virtual Common::RobotPosition getCurrentPosition() = 0;
		virtual Common::Point getCurrentTarget() const = 0;
		virtual bool cantReachTarget() const = 0;
		virtual bool isPuckCollected() const = 0;
	};
}
}
}

#endif
