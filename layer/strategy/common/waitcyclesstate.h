#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITCYCLESSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITCYCLESSTATE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class WaitCyclesState :
			public State
	{
	public:
		WaitCyclesState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee,
				  State *stateAfterTargetReached, unsigned int cycles);
		virtual ~WaitCyclesState();

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
