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

	virtual Sonar& getSonar() = 0;
	virtual Lidar& getLidar() = 0;
	virtual Camera& getCamera() = 0;
	virtual Odometry& getOdometry() = 0;
	virtual Engine& getEngine() = 0;
	virtual void updateSensorData() = 0;	
	virtual bool isValid() const = 0;
};
}
}
}

#endif
