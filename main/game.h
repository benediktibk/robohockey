#ifndef ROBOHOCKEY_MAIN_GAME_H
#define ROBOHOCKEY_MAIN_GAME_H

#include <string>
#include <QtCore/QObject>

class QTimer;

namespace RoboHockey
{
namespace Common
{
	class Logger;
	class WatchImpl;
	class SegFaultStackTracePrinter;
	class StopWatch;
}

namespace Layer
{
namespace Hardware
{
	class SensorDataRecorder;
}

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
		bool guiEnabled();
		void setLogMessagesEnabled(bool enable);
		bool logMessagesEnabled();
		void logToConsole(const std::string &message);

	private slots:
		void execute();

	protected:
		virtual void executeRobotControl() = 0;
		Layer::Autonomous::Robot& getRobot();
		Layer::Autonomous::Field& getField();
		Layer::Strategy::Common::Referee& getReferee();
		Common::Logger& getLogger();

	private:
		void printTimeInMs(const std::string &message, double time) const;

	private:
		Layer::Autonomous::Robot *m_robot;
		Layer::Autonomous::Field *m_field;
		Layer::Strategy::Common::Referee *m_referee;
		Common::Logger *m_logger;
		Common::WatchImpl *m_watch;
		Common::StopWatch *m_globalStopWatch;
		QTimer *m_timer;
		const double m_loopTimeMaximum;
		const double m_loopTimeWeight;
		double m_loopTimeAverage;
		bool m_enableGui;
		unsigned int m_blueObjectCount;
		unsigned int m_yellowObjectCount;
		unsigned int m_greenObjectCount;
		Common::SegFaultStackTracePrinter *m_stackTracePrinter;
		bool m_consoleMessagesEnabled;
		bool m_valid;
		Layer::Hardware::SensorDataRecorder *m_sensorDataRecorder;
	};
}
}

#endif


