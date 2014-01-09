#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHERMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHERMOCK_H

#include <list>
#include "common/fieldcolor.h"
#include "layer/strategy/common/colordependentpucktargetfetcher.h"

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
	class ColorDependentPuckTargetFetcherMock :
			public ColorDependentPuckTargetFetcher
	{
		public:
			ColorDependentPuckTargetFetcherMock();

			virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions() const;
			virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck() const;
			virtual RoboHockey::Common::FieldColor getColorOfTargetPucks() const;
			virtual unsigned int getNumberOfKnownPucksNotInTarget() const;

			void setNumberOfKnownPucksNotInTarget(unsigned int value);
			void setTargetPositions(const std::list<RoboHockey::Common::RobotPosition> &positions);

		private:
			unsigned int m_numberOfKnownPucksNotInTarget;
			std::list<RoboHockey::Common::RobotPosition> m_targetPositions;
		};
	}
}
}
}

#endif
