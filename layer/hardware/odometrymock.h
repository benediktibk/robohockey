#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYMOCK_H

#include "layer/hardware/odometry.h"
#include "common/point.h"

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

		virtual void setCurrentPosition(const Common::Point &position, double orientation);
		virtual Common::Point getCurrentPosition();
		virtual double getCurrentOrientation();

		unsigned int getCallsToSetCurrentPosition() const;
		unsigned int getCallsToGetCurrentPosition() const;
		unsigned int getCallsToGetCurrentOrientation() const;

	private:
		unsigned int m_callsToSetCurrentPosition;
		unsigned int m_callsToGetCurrentPosition;
		unsigned int m_callsToGetCurrentOrientation;
		Common::Point m_currentPosition;
		double m_currentOrientation;
	};
}
}
}

#endif
