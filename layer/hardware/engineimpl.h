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
		virtual bool isMoving();
		virtual double getSpeed() const;

	private:
		// forbid copies
		EngineImpl(const EngineImpl &engine);
		void operator=(const EngineImpl &engine);

	private:
		PlayerCc::Position2dProxy *m_engine;
		double m_posX;
		double m_posY;
		double m_orientation;
		bool m_posX_equal;
		bool m_posY_equal;
		bool m_orientation_equal;
		bool m_enabled;
	};
}
}
}

#endif
