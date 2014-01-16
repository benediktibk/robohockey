#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTIONRESULT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTIONRESULT_H

#include "common/compare.h"
#include "common/robotposition.h"
#include <vector>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
class FieldDetectionResult
	{
	public:
		FieldDetectionResult(Common::RobotPosition &position);

		Common::RobotPosition getTransformationDestination() const;
		bool isEqualDetectionResult(Common::RobotPosition &position) const;

		void confirmDetectionResultWithPosition(Common::RobotPosition &position);
		bool isConfirmedByBothSides() const;

	private:
		Common::RobotPosition m_newOrigin;
		Common::Compare m_compare;
		std::vector<Common::Point> m_confirmedPositionsThisSide;
		std::vector<Common::Point> m_confirmedPositionsOppositeSide;

	};
}
}
}

#endif
