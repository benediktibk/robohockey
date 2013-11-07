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
	};
}
}
}

#endif
