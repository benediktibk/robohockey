#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKTOACHIVEGOALS_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKTOACHIVEGOALS_H

#include "layer/strategy/common/drivepuck.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class DrivePuckToAchiveGoals :
			public DrivePuck
	{
	public:
		DrivePuckToAchiveGoals();

		RoboHockey::Common::RobotPosition getTargetPoint();
		RoboHockey::Common::RobotPosition getPointToCollectPuck();
	};
}
}
}
}

#endif // ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKTOACHIVEGOALS_H


