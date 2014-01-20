#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H

#include "common/robotposition.h"
#include "layer/strategy/common/state.h"
#include <list>

namespace RoboHockey
{
namespace Common
{
	class Logger;
}
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
	class DetectField :
			public Common::State
	{
	public:
		DetectField(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger,
					std::list<std::pair<unsigned int, RoboHockey::Common::RobotPosition> > previousCalibrationResults);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		void logCurrentSavedPositions();

	private:
		bool m_successful;
		unsigned int m_numberOfTries;
		std::list<std::pair<unsigned int, RoboHockey::Common::RobotPosition> > m_calibrationResults;

	};
}
}
}
}

#endif
