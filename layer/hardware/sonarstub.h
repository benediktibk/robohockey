#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARSTUB_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARSTUB_H

#include "layer/hardware/sonar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class SonarStub :
			public Sonar
	{
	public:
		virtual double getDistanceForSensor(unsigned int sensorNumber);
	};
}
}
}

#endif
