#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCK_H

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
		DrivePuck();
		virtual ~DrivePuck();

		RoboHockey::Common::RobotPosition getTargetPoint();
		RoboHockey::Common::RobotPosition getPointToCollectPuck();
	};
}
}
}
}

#endif


