#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDAR_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDAR_H

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Lidar
	{
	public:
		virtual ~Lidar();

		//! angle means actually the sensor number, therefore the real angle is angle/2
		virtual double getDistance(unsigned int angle) = 0;
		virtual void waitTillStartUpFinished() const = 0;
		unsigned int getMinimumSensorNumber() const;
		unsigned int getMaximumSensorNumber() const;
	};
}
}
}

#endif
