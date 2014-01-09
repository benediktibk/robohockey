#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERMOCK_H

#include <list>
#include "common/fieldcolor.h"
#include "layer/strategy/common/colordependendpucktargetfetcher.h"

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
	class ColorDependendPuckTargetFetcherMock :
			public ColorDependendPuckTargetFetcher
	{
		public:
			ColorDependendPuckTargetFetcherMock();

			virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions() const;
			virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck() const;
			virtual RoboHockey::Common::FieldColor getColorOfTargetPucks() const;
			virtual unsigned int getNumberOfKnownPucksNotInTarget() const;

			void setNumberOfKnownPucksNotInTarget(unsigned int value);

		private:
			unsigned int m_numberOfKnownPucksNotInTarget;
		};
	}
}
}
}

#endif
