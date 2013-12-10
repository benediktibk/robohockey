#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMOCK_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class StateMock :
			public State
	{
	public:
		StateMock(Autonomous::Robot &robot, Autonomous::Field &field, MainStateMachine::Referee &referee);

		virtual State* nextState();
		virtual void update();

		unsigned int getCallsToNextState() const;
		unsigned int getCallsToUpdate() const;
		void setNextState(State *state);

	private:
		unsigned int m_callsToNextState;
		unsigned int m_callsToUpdate;
		State *m_nextState;
	};
}
}
}
}

#endif
