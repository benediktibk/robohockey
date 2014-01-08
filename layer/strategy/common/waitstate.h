#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITSTATE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class WaitState :
			public State
	{
	public:
		WaitState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee,
				  State *stateAfterTargetReached, unsigned int cycles);
		virtual ~WaitState();

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		State *m_stateAfterWaitCycles;
		unsigned int m_cycles;
		unsigned int m_updateCounter;

	};
}
}
}
}

#endif
