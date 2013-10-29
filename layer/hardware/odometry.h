#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRY_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRY_H

namespace RoboHockey
{
namespace Common
{
class Point;
}

namespace Layer
{
namespace Hardware
{
class Odometry
{
public:
	virtual ~Odometry() { }

	virtual void setCurrentPosition(const Common::Point &position) = 0;
	virtual const Common::Point& getCurrentPosition() = 0;
};
}
}
}

#endif
