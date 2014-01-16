#include "layer/autonomous/fielddetectionresult.h"
#include "common/compare.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldDetectionResult::FieldDetectionResult(RobotPosition &position):
	m_newOrigin(position),
	m_compare(0.1)
{
	m_confirmedPositionsThisSide.reserve(7);
	m_confirmedPositionsOppositeSide.reserve(7);
}

RobotPosition FieldDetectionResult::getTransformationDestination() const
{
	return m_newOrigin;
}

bool FieldDetectionResult::isEqualDetectionResult(RobotPosition &position) const
{
	return m_compare.isFuzzyEqual(position, m_newOrigin);
}

void FieldDetectionResult::confirmDetectionResultWithPosition(RobotPosition &position)
{
	if (m_compare.isFuzzyEqual(position, m_newOrigin))
	{

	}
}

bool FieldDetectionResult::isConfirmedByBothSides() const
{
	return m_confirmedPositionsThisSide.size() > (size_t) 2 && m_confirmedPositionsOppositeSide.size() > (size_t) 2;
}

