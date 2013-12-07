#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINE_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINE_H

namespace RoboHockey
{
namespace Common
{
	class Point;
}

namespace Layer
{
namespace DataAnalysis
{
	class Engine
	{
	public:
		virtual ~Engine() { }

		virtual void goToStraight(const Common::Point &targetPosition) = 0;
		virtual void goToStraightSlowly(const Common::Point &targetPosition) = 0;
		virtual void goToStraightThrough(const Common::Point &targetPosition) = 0;
		virtual void goToStraightSlowlyBack(const Common::Point &targetPosition) = 0;
		virtual void stop() = 0;
		virtual void updateSpeedAndRotation() = 0;
		virtual void turnAround() = 0;
		virtual void turnToTarget(const Common::Point &position) = 0;
		virtual void lockForwardMovement() = 0;
		virtual void unlockForwardMovement() = 0;
		virtual bool tryingToTackleObstacle() = 0;
		virtual bool reachedTarget() const = 0;
		virtual Common::Point getCurrentTarget() const = 0;
		virtual bool isMoving() const = 0;
		virtual double getCurrentSpeed() const = 0;
		virtual void updateSensorData() = 0;
		virtual bool isGoingStraight() const = 0;
	};
}
}
}

#endif
