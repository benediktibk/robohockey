#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H

#include "layer/hardware/sonar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class SonarImpl :
		public Sonar
{
public:
	virtual double getDistanceForSensor(unsigned int sensorNumber) const;
};
}
}
}

#endif
