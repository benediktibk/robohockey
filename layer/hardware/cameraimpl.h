#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H

#include "layer/hardware/camera.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class CameraImpl :
		public Camera
{
public:
	virtual void foo() const;
};
}
}
}

#endif
