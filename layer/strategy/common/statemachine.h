#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMACHINE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMACHINE_H

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class Robot;
	class Field;
}

namespace Strategy
{
namespace MainStateMachine
{
	class Referee;
}
namespace Common
{
	class State;

	class StateMachine
	{
	public:
		StateMachine(State *initialState, Autonomous::Robot &robot, Autonomous::Field &field, MainStateMachine::Referee &referee);
		~StateMachine();

		void update();
		const State& getCurrentState() const;

	private:
		State *m_currentState;
		Autonomous::Robot &m_robot;
		Autonomous::Field &m_field;
		MainStateMachine::Referee &m_referee;
	};
}
}
}
}

#endif
