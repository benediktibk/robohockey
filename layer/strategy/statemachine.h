#ifndef ROBOHOCKEY_LAYER_STRATEGY_STATEMACHINE_H
#define ROBOHOCKEY_LAYER_STRATEGY_STATEMACHINE_H

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class Robot;
}

namespace Strategy
{
	class State;

	class StateMachine
	{
	public:
		StateMachine(State *initialState, Autonomous::Robot *robot);
		~StateMachine();

		void update();
		const State& getCurrentState() const;

	private:
		State *m_currentState;
		Autonomous::Robot *m_robot;
	};
}
}
}

#endif
