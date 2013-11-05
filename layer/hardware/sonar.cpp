#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer::Hardware;

Sonar::~Sonar()
{ }

unsigned int Sonar::getMinimumSensorNumber() const
{
	return 0;
}

unsigned int Sonar::getMaximumSensorNumber() const
{
	return 7;
}
