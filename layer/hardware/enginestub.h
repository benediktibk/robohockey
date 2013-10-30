#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINESTUB_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINESTUB_H

#include "layer/hardware/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class EngineStub :
			public Engine
	{
	public:
		virtual void setSpeed(double magnitude, double rotation);
	};
}
}
}

#endif
