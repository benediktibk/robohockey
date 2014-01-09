#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_LEAVEPUCKSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_LEAVEPUCKSTATE_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/common/colordependentpucktargetfetcher.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace DrivePuckStateMachine
{
	class LeavePuckState :
			public Common::State
	{
	public:
		LeavePuckState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, const Common::ColorDependentPuckTargetFetcher &puckTargetFetcher, bool shouldIncreaseGoalCount = false);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		const Common::ColorDependentPuckTargetFetcher &m_puckTargetFetcher;
		const bool m_shouldIncreaseGoalCount;
};
}
}
}
}

#endif
