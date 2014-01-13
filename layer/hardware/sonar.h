#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONAR_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONAR_H

#include <string>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Sonar
	{
	public:
		virtual ~Sonar();

		virtual void updateSensorData() = 0;
		virtual double getDistanceForSensor(unsigned int sensorNumber) const = 0;
		virtual void writeDataToFile(const std::string &fileName) const = 0;
		unsigned int getMinimumSensorNumber() const;
		unsigned int getMaximumSensorNumber() const;
	};
}
}
}

#endif
