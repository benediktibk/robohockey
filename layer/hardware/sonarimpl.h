#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H

#include "layer/hardware/sonar.h"

namespace PlayerCc
{
	class PlayerClient;
	class SonarProxy;
}
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
		PlayerCc::SonarProxy *m_sonar;
	};
}
}
}

#endif
