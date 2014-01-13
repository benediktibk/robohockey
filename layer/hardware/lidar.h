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

		virtual double getDistance(int angle) const = 0;
		virtual void writeDataToFile(const std::string &fileName) const = 0;
		int getMinimumSensorNumber() const;
		int getMaximumSensorNumber() const;
	};
}
}
}

#endif
