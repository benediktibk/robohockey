#include "layer/strategy/common/drivepucktohidepucks.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

DrivePuckToHidePucks::DrivePuckToHidePucks(const Autonomous::Field &field) :
	m_field(field)
{ }

list<RobotPosition> DrivePuckToHidePucks::getTargetPositions() const
{
	return m_field.getTargetsForHidingEnemyPucks();
}

list<RobotPosition> DrivePuckToHidePucks::getPositionsToCollectPuck() const
{
	return m_field.getTargetsForCollectingOnePuck(getColorOfTargetPucks());
}

FieldColor DrivePuckToHidePucks::getColorOfTargetPucks() const
{
	return m_field.getEnemyTeamColor();
}

unsigned int DrivePuckToHidePucks::getNumberOfKnownPucksNotInTarget() const
{
	return m_field.getNumberOfObjectsWithColor(getColorOfTargetPucks()) - m_field.getNumberOfHiddenPucks();
}

