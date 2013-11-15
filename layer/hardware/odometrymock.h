#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYMOCK_H

#include "layer/hardware/odometry.h"
#include "common/robotposition.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class OdometryMock :
			public Odometry
	{
	public:
		OdometryMock();

		virtual void setCurrentPosition(const Common::RobotPosition &position);
		virtual Common::RobotPosition getCurrentPosition();

		unsigned int getCallsToSetCurrentPosition() const;
		unsigned int getCallsToGetCurrentPosition() const;

	private:
		unsigned int m_callsToSetCurrentPosition;
		unsigned int m_callsToGetCurrentPosition;
		Common::RobotPosition m_currentPosition;
	};
}
}
}

#endif
