#ifndef ROBOHOCKEY_LAYER_HARDWARE_ROBOT_H
#define ROBOHOCKEY_LAYER_HARDWARE_ROBOT_H

#include "layer/hardware/sonar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class Sonar;
class Lidar;
class Camera;
class Odometry;
class Engine;

class Robot
{
public:
	virtual ~Robot() { }

	virtual const Sonar& getSonar() const = 0;
	virtual const Lidar& getLidar() const = 0;
	virtual const Camera& getCamera() const = 0;
	virtual Odometry& getOdometry() = 0;
	virtual Engine& getEngine() = 0;
};
}
}
}

#endif
