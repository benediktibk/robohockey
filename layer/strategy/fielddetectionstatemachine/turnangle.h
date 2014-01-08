#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLE_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLE_H

#include "common/robotposition.h"
#include "layer/strategy/common/state.h"
#include <vector>

namespace RoboHockey
{
namespace Common
{
	class Angle;
}
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
	class TurnAngle :
			public Common::State
	{
	public:
		TurnAngle(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Angle angle,
				  std::vector<std::pair<unsigned int, RoboHockey::Common::RobotPosition> > calibratedPositions);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		RoboHockey::Common::Angle m_angle;
		std::vector<std::pair<unsigned int, RoboHockey::Common::RobotPosition> > m_calibratedPositions;

	};
}
}
}
}

#endif
