#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCK_H

#include <vector>

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

			virtual std::vector<RoboHockey::Common::RobotPosition> getTargetPoint() = 0;
			virtual std::vector<RoboHockey::Common::RobotPosition> getPointToCollectPuck() = 0;
		};
	}
}
}
}

#endif


