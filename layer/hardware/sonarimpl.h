#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARIMPL_H

#include "layer/hardware/sonar.h"
#include <map>

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

		virtual void updateSensorData();
		virtual double getDistanceForSensor(unsigned int sensorNumber);

	private:
		SonarImpl(const SonarImpl &sonar);
		void operator=(const SonarImpl &sonar);

	private:
		PlayerCc::RangerProxy *m_sonar;
		std::map<unsigned int, double> m_lastValues;
		std::map<unsigned int, double> m_currentValues;
	};
}
}
}

#endif
