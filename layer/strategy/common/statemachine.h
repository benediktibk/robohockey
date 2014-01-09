#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMACHINE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATEMACHINE_H

#include <string>

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
namespace Common
{
	class State;
	class Referee;

	class StateMachine
	{
	public:
		StateMachine(State *initialState, Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);
		~StateMachine();

		void update();
		const State& getCurrentState() const;
		std::string getNameOfCurrentState() const;
		bool allowLogMessages() const;

	private:
		State *m_currentState;
		Autonomous::Robot &m_robot;
		Autonomous::Field &m_field;
		Referee &m_referee;
	};
}
}
}
}

#endif
