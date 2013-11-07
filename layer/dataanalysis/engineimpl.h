#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H

#include "layer/dataanalysis/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Engine;
	class Odometry;
}

namespace DataAnalysis
{
	class EngineImpl :
			public Engine
	{
	public:
		EngineImpl(Hardware::Engine &engine, Hardware::Odometry &odometry);

	virtual void goToStraight(const Common::Point &position);

	private:
		Hardware::Engine &m_engine;
		Hardware::Odometry &m_odometry;
	};
}
}
}

#endif
