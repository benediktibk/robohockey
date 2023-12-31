#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVEPUCKTOENEMYTHIRDSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVEPUCKTOENEMYTHIRDSTATE_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/common/colordependentpucktargetfetcher.h"

namespace RoboHockey
{
namespace Common
{
	class Logger;
}
namespace Layer
{
namespace Strategy
{
namespace DrivePuckStateMachine
{
	class DrivePuckToEnemyThirdState :
			public Common::State
	{
	public:
		DrivePuckToEnemyThirdState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee,
								   RoboHockey::Common::Logger &logger, Common::ColorDependentPuckTargetFetcher &puckTargetFetcher);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		Common::ColorDependentPuckTargetFetcher &m_puckTargetFetcher;

};
}
}
}
}

#endif
