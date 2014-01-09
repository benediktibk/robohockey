#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHER_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHER_H

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
	class ColorDependendPuckTargetFetcher
	{
		public:
			virtual ~ColorDependendPuckTargetFetcher() { }

			virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions() const = 0;
			virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck() const = 0;
			virtual RoboHockey::Common::FieldColor getColorOfTargetPucks() const = 0;
			virtual unsigned int getNumberOfKnownPucksNotInTarget() const = 0;
		};
	}
}
}
}

#endif


