#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDARMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDARMOCK_H

#include "layer/hardware/lidar.h"
#include <map>
#include <string>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class LidarMock :
			public Lidar
	{
	public:
		LidarMock();
		LidarMock(double defaultDistance);

		virtual double getDistance(unsigned int angle);
		unsigned int getCallsToGetDistance() const;
		void setValueForAngle(unsigned int angle, double value);
		void readSensorDataFromFile(const std::string &fileName);

	private:
		unsigned int m_callsToGetDistance;
		std::map<unsigned int, double> m_valueForAngle;
		double m_defaultDistance;
	};
}
}
}

#endif
