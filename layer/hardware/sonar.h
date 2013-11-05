#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONAR_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONAR_H

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

		virtual double getDistanceForSensor(unsigned int sensorNumber) = 0;
		unsigned int getMinimumSensorNumber() const;
		unsigned int getMaximumSensorNumber() const;
	};
}
}
}

#endif
