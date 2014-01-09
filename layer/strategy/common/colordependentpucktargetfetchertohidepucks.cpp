#include "layer/strategy/common/colordependentpucktargetfetchertohidepucks.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

ColorDependentPuckTargetFetcherToHidePucks::ColorDependentPuckTargetFetcherToHidePucks(const Autonomous::Field &field) :
	m_field(field)
{ }

list<RobotPosition> ColorDependentPuckTargetFetcherToHidePucks::getTargetPositions() const
{
	return m_field.getTargetsForHidingEnemyPucks();
}

list<RobotPosition> ColorDependentPuckTargetFetcherToHidePucks::getPositionsToCollectPuck() const
{
	return m_field.getTargetsForCollectingOnePuck(getColorOfTargetPucks());
}

FieldColor ColorDependentPuckTargetFetcherToHidePucks::getColorOfTargetPucks() const
{
	return m_field.getEnemyTeamColor();
}

unsigned int ColorDependentPuckTargetFetcherToHidePucks::getNumberOfKnownPucksNotInTarget() const
{
	return m_field.getNumberOfObjectsWithColor(getColorOfTargetPucks()) - m_field.getNumberOfHiddenPucks();
}

bool ColorDependentPuckTargetFetcherToHidePucks::isAchievingGoals() const
{
	return false;
}

