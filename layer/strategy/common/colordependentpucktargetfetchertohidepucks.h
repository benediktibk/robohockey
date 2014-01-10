#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHERTOHIDEPUCKS_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHERTOHIDEPUCKS_H

#include "layer/strategy/common/colordependentpucktargetfetcher.h"
#include "layer/autonomous/field.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class ColorDependentPuckTargetFetcherToHidePucks :
			public ColorDependentPuckTargetFetcher
	{
	public:
		ColorDependentPuckTargetFetcherToHidePucks(const Autonomous::Field &field);

		virtual std::list<RoboHockey::Common::RobotPosition> getTargetPositions() const;
		virtual std::list<RoboHockey::Common::RobotPosition> getPositionsToCollectPuck() const;
		virtual RoboHockey::Common::FieldColor getColorOfTargetPucks() const;
		virtual unsigned int getNumberOfKnownPucksNotInTarget() const;
		virtual unsigned int getNumberOfKnownPucksNotInEnemyThird() const;
		virtual bool isAchievingGoals() const;

	private:
		const Autonomous::Field &m_field;

	};
}
}
}
}

#endif


