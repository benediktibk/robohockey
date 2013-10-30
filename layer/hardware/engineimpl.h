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

		virtual void setSpeed(double magnitude, double rotation);

	private:
		PlayerCc::Position2dProxy *m_engine;
	};
}
}
}

#endif
