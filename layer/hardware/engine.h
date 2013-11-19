#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINE_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINE_H

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
		double getMaximumRotation() const;
		double getMaximumSpeed() const;
		double getMinimumRotation() const;
		double getMinimumSpeed() const;
		virtual bool isMoving() const = 0;

	private:
		static const double m_maximumMagnitude;
		static const double m_minimumMagnitude;
		static const double m_maximumRotation;
		static const double m_minimumRotation;
	};
}
}
}

#endif
