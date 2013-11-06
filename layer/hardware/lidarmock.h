#ifndef ROBOHOCKEY_LAYER_HARDWARE_LIDARMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_LIDARMOCK_H

#include "layer/hardware/lidar.h"

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

		virtual double getDistance(unsigned int angle);
		unsigned int getCallsToGetDistance() const;
		virtual bool isValid() const;

	private:
		unsigned int m_callsToGetDistance;
	};
}
}
}

#endif
