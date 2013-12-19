#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_FINDPUCKSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_FINDPUCKSTATE_H

#include "layer/strategy/common/driveto.h"
#include "layer/strategy/common/drivepuck.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace DrivePuckStateMachine
{
	class FindPuckState :
			public Common::DriveTo
	{
	public:
		FindPuckState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Layer::Strategy::Common::DrivePuck *drivePuck);

	private:
};
}
}
}
}

#endif
