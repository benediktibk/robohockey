#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVEPUCKTOPOSITIONSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVEPUCKTOPOSITIONSTATE_H

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
	class DrivePuckToPositionState :
			public Common::State
	{
	public:
		DrivePuckToPositionState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, const Common::ColorDependendPuckTargetFetcher &drivePuck);

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
