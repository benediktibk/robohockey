#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_SENSORDATAPLAYER_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_SENSORDATAPLAYER_H

#include <string>

namespace RoboHockey
{
namespace Common
{
	class WatchMock;
	class LoggerMock;
	class Point;
}

namespace Layer
{
namespace Hardware
{
	class RobotMock;
}

namespace DataAnalysis
{
	class DataAnalyser;
}

namespace Autonomous
{
	class Field;
	class Robot;

	class SensorDataPlayer
	{
	public:
		SensorDataPlayer(const std::string &path);
		virtual ~SensorDataPlayer();

		void loadNextRound();
		unsigned int getMaximumRoundCount() const;
		bool countOfColoredObjectsDecreased() const;
		unsigned int getBlueObjectCount() const;
		unsigned int getYellowObjectCount() const;
		unsigned int getGreenObjectCount() const;
		Field &getField();
		Common::Point getCurrentPosition() const;

	private:
		void loadNextRound(unsigned int roundCount);

	private:
		std::string m_path;
		unsigned int m_maximumRoundCount;
		unsigned int m_roundCount;
		Common::WatchMock *m_watch;
		Common::LoggerMock *m_logger;
		Hardware::RobotMock *m_hardwareRobot;
		DataAnalysis::DataAnalyser *m_dataAnalyser;
		Robot *m_robot;
		Field *m_field;
		unsigned int m_oldBlueObjectCount;
		unsigned int m_oldYellowObjectCount;
		unsigned int m_oldGreenObjectCount;
		unsigned int m_blueObjectCount;
		unsigned int m_yellowObjectCount;
		unsigned int m_greenObjectCount;
	};
}
}
}

#endif


