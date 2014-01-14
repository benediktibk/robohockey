#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKS_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKS_H

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
class HideEnemyPucks :
		public Common::State
	{
	public:
		HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger);
		virtual ~HideEnemyPucks();

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
