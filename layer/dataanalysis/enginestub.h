#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINESTUB_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINESTUB_H

#include "layer/dataanalysis/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class EngineStub :
			public Engine
	{
	public:
		virtual void goToStraight(const Common::Point &position);
	};
}
}
}

#endif
