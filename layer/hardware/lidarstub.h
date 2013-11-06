#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDARSTUB_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDARSTUB_H

#include "layer/hardware/lidar.h"
#include <map>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class LidarStub :
			public Lidar
	{
	public:
		LidarStub();
		LidarStub(double defaultDistance);

		virtual double getDistance(unsigned int angle);
		void setValueForAngle(unsigned int angle, double value);
		virtual void waitTillStartUpFinished() const;

	private:
		std::map<unsigned int, double> m_valueForAngle;
		double m_defaultDistance;
	};
}
}
}

#endif
