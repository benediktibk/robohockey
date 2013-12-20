#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H

#include "common/robotposition.h"
#include "layer/strategy/common/state.h"
#include <vector>

namespace RoboHockey
{
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
		DetectField(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee,
					std::vector<RoboHockey::Common::RobotPosition> previousCalibrationResults);

		virtual State* nextState();

	protected:
		virtual void updateInternal();

	private:
		bool m_successful;
		unsigned int m_numberOfTries;
		std::vector<RoboHockey::Common::RobotPosition> m_calibrationResults;

	};
}
}
}
}

#endif
