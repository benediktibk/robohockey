#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDAR_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDAR_H

#include <string>

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
		virtual double getDistance(int angle) = 0;
		virtual void writeDataToFile(const std::string &fileName) = 0;
		int getMinimumSensorNumber() const;
		int getMaximumSensorNumber() const;
	};
}
}
}

#endif
