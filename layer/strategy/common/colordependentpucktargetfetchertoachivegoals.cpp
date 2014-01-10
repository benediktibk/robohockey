#include "layer/strategy/common/colordependentpucktargetfetchertoachivegoals.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

ColorDependentPuckTargetFetcherToAchiveGoals::ColorDependentPuckTargetFetcherToAchiveGoals(const Field &field) :
	m_field(field)
{ }

list<RobotPosition> ColorDependentPuckTargetFetcherToAchiveGoals::getTargetPositions() const
{
	return m_field.getTargetsForScoringGoals();
}

list<RobotPosition> ColorDependentPuckTargetFetcherToAchiveGoals::getPositionsToCollectPuck() const
{
	return m_field.getTargetsForCollectingOnePuck(getColorOfTargetPucks());
}

FieldColor ColorDependentPuckTargetFetcherToAchiveGoals::getColorOfTargetPucks() const
{
	return m_field.getOwnTeamColor();
}

unsigned int ColorDependentPuckTargetFetcherToAchiveGoals::getNumberOfKnownPucksNotInTarget() const
{
	return m_field.getNumberOfObjectsWithColor(getColorOfTargetPucks()) - m_field.getNumberOfAchievedGoals();
}

unsigned int ColorDependentPuckTargetFetcherToAchiveGoals::getNumberOfKnownPucksNotInEnemyThird() const
{
	return m_field.getNumberOfObjectsWithColor(getColorOfTargetPucks()) - m_field.getNumberOfPuckInEnemyThird();
}

bool ColorDependentPuckTargetFetcherToAchiveGoals::isAchievingGoals() const
{
	return false;
}

