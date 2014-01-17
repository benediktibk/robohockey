#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHER_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHER_H

#include <list>
#include "common/fieldcolor.h"

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
}
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class ColorDependentPuckTargetFetcher
	{
		public:
			ColorDependentPuckTargetFetcher();
			virtual ~ColorDependentPuckTargetFetcher() { }

			virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions() const = 0;
			virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck() const = 0;
			virtual RoboHockey::Common::FieldColor getColorOfTargetPucks() const = 0;
			virtual unsigned int getNumberOfKnownPucksNotInTarget() const = 0;
			virtual unsigned int getNumberOfKnownPucksNotInEnemyThird() const = 0;
			virtual bool isAchievingGoals() const = 0;
			virtual bool isCantReachTargetLimitReached() const;
			virtual void resetCantReachTargetCounter();
			virtual void increaseCantReachTargetCounter();

		private:
			unsigned int m_cantReachTargetCounter;

		};
}
}
}
}

#endif


