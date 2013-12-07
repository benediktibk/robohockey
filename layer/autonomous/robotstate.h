#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTSTATE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTSTATE_H

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	enum RobotState {RobotStateWaiting, RobotStateDrivingStraightPart, RobotStateDrivingTurningPart, RobotStateTurnAround, RobotStateCollectingPuck, RobotStateLeavingPuck, RobotStateTurnTo};
}
}
}

#endif
