#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATE_H

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
    class State
	{
	public:
		State(Autonomous::Robot &robot, Autonomous::Field &field, MainStateMachine::Referee &referee);
		virtual ~State();

		virtual State* nextState() = 0;
		virtual void update() = 0;

	protected:
		Autonomous::Robot &m_robot;
        Autonomous::Field &m_field;
		MainStateMachine::Referee &m_referee;
	};
}
}
}
}

#endif
