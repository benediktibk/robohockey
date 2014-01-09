#include "layer/strategy/common/colordependendpucktargetfetchertoachivegoals.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

ColorDependendPuckTargetFetcherToAchiveGoals::ColorDependendPuckTargetFetcherToAchiveGoals(const Field &field) :
	m_field(field)
{ }

list<RobotPosition> ColorDependendPuckTargetFetcherToAchiveGoals::getTargetPositions() const
{
	return m_field.getTargetsForScoringGoals();
}

list<RobotPosition> ColorDependendPuckTargetFetcherToAchiveGoals::getPositionsToCollectPuck() const
{
	return m_field.getTargetsForCollectingOnePuck(getColorOfTargetPucks());
}

FieldColor ColorDependendPuckTargetFetcherToAchiveGoals::getColorOfTargetPucks() const
{
	return m_field.getOwnTeamColor();
}

unsigned int ColorDependendPuckTargetFetcherToAchiveGoals::getNumberOfKnownPucksNotInTarget() const
{
	return m_field.getNumberOfObjectsWithColor(getColorOfTargetPucks()) - m_field.getNumberOfAchievedGoals();
}

