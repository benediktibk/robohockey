#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARMOCK_H

#include "layer/hardware/sonar.h"
#include <map>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class SonarMock :
			public Sonar
	{
	public:
		SonarMock();

		virtual double getDistanceForSensor(unsigned int sensorNumber);
		unsigned int getCallsToGetDistanceForSensor() const;
		void setValue(unsigned int sensorNumber, double value);

	private:
		unsigned int m_callsToGetDistanceForSensor;
		std::map<unsigned int, double> m_values;
	};
}
}
}

#endif
