#include "layer/autonomous/fielddetectionresult.h"
#include "common/compare.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldDetectionResult::FieldDetectionResult(RobotPosition &position):
	m_newOrigin(position),
	m_compare(0.1),
	m_confirmedPositionsThisSide(0),
	m_confirmedPositionsOppositeSide(0)
{ }

RobotPosition FieldDetectionResult::getTransformationDestination() const
{
	return m_newOrigin;
}

bool FieldDetectionResult::isEqualDetectionResult(RobotPosition &position) const
{
	return m_compare.isFuzzyEqual(position, m_newOrigin);
}

void FieldDetectionResult::confirmDetectionResultWithPosition(RobotPosition &position, unsigned int numberOfStones, bool onOppositeSide)
{
	if (m_compare.isFuzzyEqual(position, m_newOrigin))
	{
		if (!onOppositeSide && m_confirmedPositionsThisSide < numberOfStones)
			m_confirmedPositionsThisSide = numberOfStones;
		else if (onOppositeSide && m_confirmedPositionsOppositeSide < numberOfStones)
			m_confirmedPositionsOppositeSide = numberOfStones;
	}
}

bool FieldDetectionResult::isConfirmedByBothSides() const
{
	return m_confirmedPositionsThisSide > (unsigned int) 2 && m_confirmedPositionsOppositeSide > (unsigned int) 2;
}

unsigned int FieldDetectionResult::getNumberOfBorderStones() const
{
	return m_confirmedPositionsThisSide + m_confirmedPositionsOppositeSide;
}

