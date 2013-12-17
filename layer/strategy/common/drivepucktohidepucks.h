#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKTOHIDEPUCKS_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKTOHIDEPUCKS_H

#include "layer/strategy/common/drivepuck.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class DrivePuckToHidePucks :
			public DrivePuck
	{
	public:
		DrivePuckToHidePucks();

		RoboHockey::Common::RobotPosition getTargetPoint();
		RoboHockey::Common::RobotPosition getPointToCollectPuck();
	};
}
}
}
}

#endif


