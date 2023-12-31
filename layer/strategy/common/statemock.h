#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMOCK_H

#include "layer/strategy/common/state.h"

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
	class StateMock :
			public State
	{
	public:
		StateMock(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee, RoboHockey::Common::Logger &logger);
		StateMock(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee, RoboHockey::Common::Logger &logger, bool callUpdateOnlyOnce);

		virtual State* nextState();
		virtual std::string getName();

		unsigned int getCallsToNextState() const;
		unsigned int getCallsToUpdate() const;
		void setNextState(State *state);

	protected:
		virtual void updateInternal();

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
