#include "layer/hardware/lidar.h"

using namespace RoboHockey::Layer::Hardware;

Lidar::~Lidar()
{ }

int Lidar::getMinimumSensorNumber() const
{
	return 0;
}

int Lidar::getMaximumSensorNumber() const
{
	return 360;
}
