#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOT_H

#include "layer/autonomous/fieldobject.h"
#include <vector>
#include <list>

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

	class Route;

	class Robot
	{
	public:
		virtual ~Robot() { }

		virtual void goTo(const std::list<Common::RobotPosition> &possibleTargets) = 0;
		virtual void turnTo(const Common::Point &position) = 0;
		virtual bool stuckAtObstacle() = 0;
		virtual bool reachedTarget() = 0;
		virtual void updateActuators(const Field &field) = 0;
		virtual void updateSensorData() = 0;
		virtual void stop() = 0;
		virtual void collectPuckInFront(const Common::Point &puckPosition) = 0;
		virtual void updatePuckPosition(const Common::Point &puckPosition) = 0;
		virtual void leaveCollectedPuck() = 0;
		virtual bool isMoving() const = 0;
		virtual void turnAround() = 0;
		virtual Common::RobotPosition getCurrentPosition() const = 0;
		virtual std::list<Common::Point> getAllRoutePoints() const = 0;
		virtual bool cantReachTarget() const = 0;
		virtual bool isPuckCollected() const = 0;
		virtual bool isPuckCollectable() const = 0;
		virtual bool isCollectingPuck() const = 0;
		virtual bool isRotating() const = 0;
	};
}
}
}

#endif
