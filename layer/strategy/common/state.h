#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATE_H

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
	class Referee;

	class State
	{
	public:
		State(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee, bool callUpdateOnlyOnce);
		virtual ~State();

		virtual State* nextState() = 0;
		void update();
		virtual std::string getName() = 0;
		virtual bool allowLogMessages();

	protected:
		virtual void updateInternal() = 0;

	protected:
		Autonomous::Robot &m_robot;
		Autonomous::Field &m_field;
		Referee &m_referee;

	private:
		bool m_callUpdateOnlyOnce;
		bool m_updateAlreadyCalled;
	};
}
}
}
}

#endif
