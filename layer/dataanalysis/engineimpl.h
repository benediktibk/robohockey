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
}

namespace DataAnalysis
{
class EngineImpl :
		public Engine
{
public:
	EngineImpl(Hardware::Engine &engine);

	virtual void setSpeed(double magnitude, double rotation);

private:
	Hardware::Engine &m_engine;
};
}
}
}

#endif
