#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H

#include "layer/hardware/sonar.h"

namespace PlayerCc
{
	class PlayerClient;
	class RangerProxy;
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
		~SonarImpl();

		virtual double getDistanceForSensor(unsigned int sensorNumber);

	private:
		SonarImpl(const SonarImpl &sonar);
		void operator=(const SonarImpl &sonar);

	private:
		PlayerCc::RangerProxy *m_sonar;
	};
}
}
}

#endif
