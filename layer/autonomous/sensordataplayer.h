#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_SENSORDATAPLAYER_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_SENSORDATAPLAYER_H

#include <string>

namespace RoboHockey
{
namespace Common
{
	class WatchMock;
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

	private:
		void loadNextRound(unsigned int roundCount);

	private:
		std::string m_path;
		unsigned int m_maximumRoundCount;
		unsigned int m_roundCount;
		Common::WatchMock *m_watch;
		Hardware::RobotMock *m_hardwareRobot;
		DataAnalysis::DataAnalyser *m_dataAnalyser;
		Robot *m_robot;
		Field *m_field;
	};
}
}
}

#endif


