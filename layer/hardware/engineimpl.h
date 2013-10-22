#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINEIMPL_H

#include "layer/hardware/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class EngineImpl :
		public Engine
{
public:
	virtual void setSpeed(double magnitude, double rotation);
};
}
}
}

#endif
