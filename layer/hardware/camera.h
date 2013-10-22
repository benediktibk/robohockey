#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERA_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERA_H

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class Camera
{
public:
	virtual ~Camera() { }

	virtual void foo() const = 0;
};
}
}
}

#endif
