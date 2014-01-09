#include "layer/strategy/common/colordependendpucktargetfetchertohidepucks.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

ColorDependendPuckTargetFetcherToHidePucks::ColorDependendPuckTargetFetcherToHidePucks(const Autonomous::Field &field) :
	m_field(field)
{ }

list<RobotPosition> ColorDependendPuckTargetFetcherToHidePucks::getTargetPositions() const
{
	return m_field.getTargetsForHidingEnemyPucks();
}

list<RobotPosition> ColorDependendPuckTargetFetcherToHidePucks::getPositionsToCollectPuck() const
{
	return m_field.getTargetsForCollectingOnePuck(getColorOfTargetPucks());
}

FieldColor ColorDependendPuckTargetFetcherToHidePucks::getColorOfTargetPucks() const
{
	return m_field.getEnemyTeamColor();
}

unsigned int ColorDependendPuckTargetFetcherToHidePucks::getNumberOfKnownPucksNotInTarget() const
{
	return m_field.getNumberOfObjectsWithColor(getColorOfTargetPucks()) - m_field.getNumberOfHiddenPucks();
}

