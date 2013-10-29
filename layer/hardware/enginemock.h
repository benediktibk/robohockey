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

private:
	unsigned int m_callsToSetSpeed;
};
}
}
}

#endif
