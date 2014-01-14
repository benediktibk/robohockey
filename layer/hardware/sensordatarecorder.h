#ifndef ROBOHOCKEY_LAYER_HARDWARE_SENSORDATARECORDER_H
#define ROBOHOCKEY_LAYER_HARDWARE_SENSORDATARECORDER_H

#include <string>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Robot;

	class SensorDataRecorder
	{
	public:
		SensorDataRecorder(const Robot &robot, const std::string &path);

		void recordCurrentValues(bool recordCamera);

	private:
		const Robot &m_robot;
		const std::string m_path;
		unsigned int m_roundCount;
	};
}
}
}

#endif


