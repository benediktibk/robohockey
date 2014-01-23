#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATE_H

#include <string>

namespace RoboHockey
{
namespace Common
{
	class Logger;
}
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
		State(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee, RoboHockey::Common::Logger &logger, bool callUpdateOnlyOnce);
		virtual ~State();

		virtual State* nextState() = 0;
		void update();
		virtual std::string getName() = 0;
		virtual bool allowLogMessages();
		bool updateAlreadyCalled() const;

	protected:
		virtual void updateInternal() = 0;

	protected:
		Autonomous::Robot &m_robot;
		Autonomous::Field &m_field;
		Referee &m_referee;
		RoboHockey::Common::Logger &m_logger;

	private:
		bool m_callUpdateOnlyOnce;
		bool m_updateAlreadyCalled;
	};
}
}
}
}

#endif
