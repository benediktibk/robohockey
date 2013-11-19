#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINEMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINEMOCK_H

#include "layer/hardware/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class EngineMock :
			public Engine
	{
	public:
		EngineMock();

		virtual void setSpeed(double magnitude, double rotation);
		unsigned int getCallsToSetSpeed() const;
		double getLastMagnitude() const;
		double getLastRotation() const;
		virtual bool isMoving() const;

	private:
		unsigned int m_callsToSetSpeed;
		double m_lastMagnitude;
		double m_lastRotation;
	};
}
}
}

#endif
