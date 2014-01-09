#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOCOLLECTPUCKSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOCOLLECTPUCKSTATE_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/common/colordependendpucktargetfetcher.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace DrivePuckStateMachine
{
	class DriveToCollectPuckState :
			public Common::State
	{
	public:
		DriveToCollectPuckState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, const Common::ColorDependendPuckTargetFetcher &drivePuck);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		const Common::ColorDependendPuckTargetFetcher &m_drivePuck;
};
}
}
}
}

#endif
