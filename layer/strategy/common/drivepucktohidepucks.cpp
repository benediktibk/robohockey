#include "layer/strategy/common/drivepucktohidepucks.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

DrivePuckToHidePucks::DrivePuckToHidePucks(Autonomous::Field &field) :
	m_field(field)
{ }

list<RobotPosition> DrivePuckToHidePucks::getTargetPositions()
{
	return m_field.getTargetsForHidingEnemyPucks();
}

list<RobotPosition> DrivePuckToHidePucks::getPositionsToCollectPuck()
{
	return m_field.getTargetsForCollectingOnePuck(m_field.getEnemyTeamColor());
}

FieldColor DrivePuckToHidePucks::getColorOfTargetPucks()
{
	return FieldColorUnknown;
}

unsigned int DrivePuckToHidePucks::getNumberOfKnownPucksNotInTarget()
{
	return 0;
}

