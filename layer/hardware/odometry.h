#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRY_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRY_H

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class Odometry
{
public:
	virtual ~Odometry() { }

	virtual void foo() const = 0;
};
}
}
}

#endif
