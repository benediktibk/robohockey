#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERTOACHIVEGOALS_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERTOACHIVEGOALS_H

#include "layer/strategy/common/colordependendpucktargetfetcher.h"
#include "layer/autonomous/field.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class ColorDependendPuckTargetFetcherToAchiveGoals :
			public ColorDependendPuckTargetFetcher
	{
	public:
		ColorDependendPuckTargetFetcherToAchiveGoals(const Autonomous::Field &field);

		virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions() const;
		virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck() const;
		virtual RoboHockey::Common::FieldColor getColorOfTargetPucks() const;
		virtual unsigned int getNumberOfKnownPucksNotInTarget() const;

	private:
		const Autonomous::Field &m_field;
	};
}
}
}
}

#endif


