#ifndef ROBOHOCKEY_MAIN_GAME_H
#define ROBOHOCKEY_MAIN_GAME_H

#include <string>

class QApplication;
class QEventLoop;

namespace RoboHockey
{
namespace Common
{
	class Watch;
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
	class Referee;
}
}

namespace Main
{
	class Game
	{
	public:
		Game(int argc, char **argv);
		virtual ~Game();

		void execute();
		virtual bool keepRunning() const = 0;

	protected:
		virtual void executeRobotControl() = 0;
		Layer::Autonomous::Robot& getRobot();
		Layer::Autonomous::Field& getField();
		Layer::Strategy::Referee& getReferee();

	private:
		void printTimeInMs(const std::string &message, double time) const;

	private:
		Layer::Autonomous::Robot *m_robot;
		Layer::Autonomous::Field *m_field;
		Layer::Strategy::Referee *m_referee;
		Common::Watch *m_watch;
		QApplication *m_application;
		QEventLoop *m_eventLoop;
	};
}
}

#endif


