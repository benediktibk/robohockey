#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H

#include "layer/hardware/sonar.h"
#include <player-3.0/libplayerc++/playerc++.h>

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
	SonarImpl(PlayerCc::PlayerClient *playerClient);

	virtual double getDistanceForSensor(unsigned int sensorNumber);

private:
	PlayerCc::SonarProxy m_sonar;
};
}
}
}

#endif
