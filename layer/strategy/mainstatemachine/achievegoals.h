#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_ACHIEVEGOALS_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_ACHIEVEGOALS_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/common/statemachine.h"

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
namespace Common
{
	class ColorDependentPuckTargetFetcher;
}

namespace MainStateMachine
{
	class AchieveGoals :
			public Common::State
	{
	public:
		AchieveGoals(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger);
		virtual ~AchieveGoals();

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		Common::StateMachine *m_puckTargetFetcherStateMachine;
		Common::ColorDependentPuckTargetFetcher *m_puckTargetFetcher;
	};
}
}
}
}

#endif
