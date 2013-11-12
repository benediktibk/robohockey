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
		virtual void stop() = 0;
		virtual void updateSpeedAndRotation() = 0;
		virtual void turnAround() = 0;
		virtual void turnToTarget(const Common::Point &position) = 0;
	};
}
}
}

#endif
