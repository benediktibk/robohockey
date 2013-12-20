#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVEPUCKMOCK_H

#include <list>
#include "common/fieldcolor.h"
#include "layer/strategy/common/drivepuck.h"

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
}
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class DrivePuckMock :
			public DrivePuck
	{
		public:
			DrivePuckMock();

			virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions();
			virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck();
			virtual RoboHockey::Common::FieldColor getColorOfTargetPucks();
			virtual unsigned int getNumberOfKnownPucksNotInTarget();

			void setNumberOfKnownPucksNotInTarget(unsigned int value);

		private:
			unsigned int m_numberOfKnownPucksNotInTarget;
		};
	}
}
}
}

#endif
