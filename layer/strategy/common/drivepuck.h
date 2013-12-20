#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCK_H

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
	class DrivePuck
	{
		public:
			virtual ~DrivePuck() { }

			virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions() = 0;
			virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck() = 0;
			virtual RoboHockey::Common::FieldColor getColorOfTargetPucks() = 0;
			virtual unsigned int getNumberOfKnownPucksNotInTarget() = 0;
		};
	}
}
}
}

#endif


