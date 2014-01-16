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
		FieldDetectionResult(Common::RobotPosition &position, unsigned int numberOfStones, bool onOppositeSide);

		Common::RobotPosition getTransformationDestination() const;
		bool isEqualDetectionResult(Common::RobotPosition &position) const;

		void confirmDetectionResultWithPosition(Common::RobotPosition &position, unsigned int numberOfStones, bool onOppositeSide);
		bool isConfirmedByBothSides() const;
		unsigned int getNumberOfBorderStones() const;

	private:
		Common::RobotPosition m_newOrigin;
		Common::Compare m_compare;
		unsigned int m_confirmedPositionsThisSide;
		unsigned int m_confirmedPositionsOppositeSide;

	};
}
}
}

#endif
