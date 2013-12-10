#ifndef ROBOHOCKEY_MAIN_GAME_H
#define ROBOHOCKEY_MAIN_GAME_H

#include <string>
#include <QtCore/QObject>

class QTimer;

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
namespace Common
{
	class Referee;
}
}
}

namespace Main
{
	class Game :
			public QObject
	{
		Q_OBJECT

	public:
		Game(int argc, char **argv);
		virtual ~Game();

		virtual bool keepRunning() const = 0;

	private slots:
		void execute();

	protected:
		virtual void executeRobotControl() = 0;
		Layer::Autonomous::Robot& getRobot();
		Layer::Autonomous::Field& getField();
		Layer::Strategy::Common::Referee& getReferee();

	private:
		void printTimeInMs(const std::string &message, double time) const;

	private:
		Layer::Autonomous::Robot *m_robot;
		Layer::Autonomous::Field *m_field;
		Layer::Strategy::Common::Referee *m_referee;
		Common::Watch *m_watch;
		QTimer *m_timer;
	};
}
}

#endif


