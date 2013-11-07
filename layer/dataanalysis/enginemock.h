#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEMOCK_H

#include "layer/dataanalysis/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class EngineMock :
			public Engine
	{
	public:
		EngineMock();

		virtual void goToStraight(const Common::Point &position);
		virtual void updateSpeedAndMagnitude();
		virtual void stop();

		unsigned int getCallsToGoToStraight() const;

	private:
		unsigned int m_callsToGoToStraight;
	};
}
}
}

#endif
