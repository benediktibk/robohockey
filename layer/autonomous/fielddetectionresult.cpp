#include "layer/autonomous/fielddetectionresult.h"
#include "common/compare.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldDetectionResult::FieldDetectionResult(Common::RobotPosition &position, unsigned int numberOfStones, bool onOppositeSide):
	m_newOrigin(position),
	m_confirmedPositionsThisSide(0),
	m_confirmedPositionsOppositeSide(0)
{
	confirmDetectionResultWithPosition(position, numberOfStones, onOppositeSide);
}

RobotPosition FieldDetectionResult::getTransformationDestination() const
{
	return m_newOrigin;
}

bool FieldDetectionResult::isEqualDetectionResult(RobotPosition &position) const
{
	Compare angleCompare(0.5);
	Compare pointCompare(0.12);
	return pointCompare.isFuzzyEqual(position.getPosition(), m_newOrigin.getPosition())
			&& angleCompare.isFuzzyEqual(position.getOrientation(), m_newOrigin.getOrientation());
}

void FieldDetectionResult::confirmDetectionResultWithPosition(RobotPosition &position, unsigned int numberOfStones, bool onOppositeSide)
{
	if (isEqualDetectionResult(position))
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

unsigned int FieldDetectionResult::numberOfNearStones()
{
	return m_confirmedPositionsThisSide;
}

unsigned int FieldDetectionResult::numberOfOppositeStones()
{
	return m_confirmedPositionsOppositeSide;
}

