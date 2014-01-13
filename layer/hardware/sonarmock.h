#ifndef ROBOHOCKEY_LAYER_HARDWARE_SONARMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_SONARMOCK_H

#include "layer/hardware/sonar.h"
#include <map>
#include <string>

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

		virtual void updateSensorData();
		virtual double getDistanceForSensor(unsigned int sensorNumber) const;
		void setValue(unsigned int sensorNumber, double value);
		virtual void writeDataToFile(const std::string &fileName) const;
		void readDataFromFile(const std::string &fileName);

	private:
		std::map<unsigned int, double> m_values;
	};
}
}
}

#endif
