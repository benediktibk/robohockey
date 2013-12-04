#ifndef ROBOHOCKEY_LAYER_STRATEGY_STATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_STATE_H

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
    class Referee;
    class State
	{
	public:
        State(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);
		virtual ~State();

		virtual State* nextState() = 0;
		virtual void update() = 0;

	protected:
		Autonomous::Robot &m_robot;
        Autonomous::Field &m_field;
        Referee &m_referee;
	};
}
}
}

#endif
