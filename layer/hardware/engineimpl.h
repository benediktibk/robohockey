#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINEIMPL_H

#include "layer/hardware/engine.h"
#include "common/robotposition.h"
#include "common/compare.h"

namespace PlayerCc
{
	class PlayerClient;
	class Position2dProxy;
}
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
		EngineImpl(PlayerCc::PlayerClient *playerClient);
		~EngineImpl();

		virtual void setSpeed(double magnitude, double rotation);
		virtual bool isMoving() const;
		virtual double getSpeed() const;
		virtual void setEnabled(bool value);
		virtual void writeDataToFile(const std::string &fileName) const;
		virtual void updateSensorData();

	private:
		// forbid copies
		EngineImpl(const EngineImpl &engine);
		void operator=(const EngineImpl &engine);

	private:
		PlayerCc::Position2dProxy *m_engine;
		double m_lastXPos;
		double m_lastYPos;
		double m_lastOrientation;
		double m_currentXPos;
		double m_currentYPos;
		double m_currentOrientation;
		bool m_enabled;
	};
}
}
}

#endif
