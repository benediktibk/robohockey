#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKTOACHIVEGOALS_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKTOACHIVEGOALS_H

#include "layer/strategy/common/drivepuck.h"
#include "layer/autonomous/field.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class DrivePuckToAchiveGoals :
			public DrivePuck
	{
	public:
		DrivePuckToAchiveGoals(Autonomous::Field &field);

		virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions();
		virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck();
		virtual RoboHockey::Common::FieldColor getColorOfTargetPucks();
		virtual unsigned int getNumberOfKnownPucksNotInTarget();

	private:
		Autonomous::Field &m_field;
	};
}
}
}
}

#endif


