#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINEMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINEMOCK_H

#include "layer/hardware/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class EngineMock :
			public Engine
	{
	public:
		EngineMock();

		virtual void setSpeed(double magnitude, double rotation);
		virtual bool isMoving() const;
		virtual double getSpeed() const;
		virtual double getRotationSpeed() const;
		virtual void setEnabled(bool value);
		virtual void writeDataToFile(const std::string &fileName) const;
		virtual void updateSensorData();

		unsigned int getCallsToSetSpeed() const;
		unsigned int getCallsToSetEnabled() const;
		bool getEnabled() const;
		double getLastMagnitude() const;
		double getLastRotation() const;
		void setIsMoving(bool value);
		void readDataFromFile(const std::string &fileName);
		void setRotationSpeed(double value);

	private:
		unsigned int m_callsToSetSpeed;
		unsigned int m_callsToSetEnabled;
		double m_lastMagnitude;
		double m_lastRotation;
		bool m_enabled;
		bool m_isMoving;
		double m_speed;
		double m_rotationSpeed;
	};
}
}
}

#endif
