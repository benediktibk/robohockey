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

		std::vector<RoboHockey::Common::RobotPosition> getTargetPoint();
		std::vector<RoboHockey::Common::RobotPosition> getPointToCollectPuck();
	};
}
}
}
}

#endif


