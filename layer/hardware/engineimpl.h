#ifndef ROBOHOCKEY_LAYER_HARDWARE_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ENGINEIMPL_H

#include "layer/hardware/engine.h"

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

	private:
		double limitToTresholds(double value, double lowerBound, double upperBound) const;

	private:
		// forbid copies
		EngineImpl(const EngineImpl &engine);
		void operator=(const EngineImpl &engine);

	private:
		PlayerCc::Position2dProxy *m_engine;

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
