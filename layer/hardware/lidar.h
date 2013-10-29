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
	virtual ~Lidar() { }

	virtual double getDistance(unsigned int angle) = 0;
};
}
}
}

#endif
