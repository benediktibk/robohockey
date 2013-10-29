#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H

#include "layer/dataanalysis/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class EngineImpl :
		public Engine
{
public:
	virtual void setSpeed(double magnitude, double rotation);
};
}
}
}

#endif
