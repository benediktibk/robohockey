#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKS_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKS_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/common/statemachine.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace MainStateMachine
{
class HideEnemyPucks :
		public Common::State
	{
	public:
		HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);
		virtual ~HideEnemyPucks();

		virtual State* nextState();
		virtual void update();

	private:
		Common::StateMachine *m_drivePuckStateMachine;
	};
}
}
}
}

#endif
