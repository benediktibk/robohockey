#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINE_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINE_H

#include <string>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Engine
	{
	public:
		virtual ~Engine() { }

		virtual void setSpeed(double magnitude, double rotation) = 0;
		virtual bool isMoving() const = 0;
		virtual double getSpeed() const = 0;
		virtual void setEnabled(bool value) = 0;
		virtual void writeDataToFile(const std::string &fileName) const = 0;
		virtual void updateSensorData() = 0;
	};
}
}
}

#endif
