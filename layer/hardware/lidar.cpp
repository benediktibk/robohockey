#include "layer/hardware/lidar.h"

using namespace RoboHockey::Layer::Hardware;

Lidar::~Lidar()
{ }

unsigned int Lidar::getMinimumSensorNumber() const
{
	return 0;
}

unsigned int Lidar::getMaximumSensorNumber() const
{
	return 360;
}
