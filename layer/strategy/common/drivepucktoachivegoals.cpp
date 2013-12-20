#include "layer/strategy/common/drivepucktoachivegoals.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

DrivePuckToAchiveGoals::DrivePuckToAchiveGoals(Field &field) :
	m_field(field)
{ }

list<RobotPosition> DrivePuckToAchiveGoals::getTargetPositions()
{
	return m_field.getTargetsForScoringGoals();
}

list<RobotPosition> DrivePuckToAchiveGoals::getPositionsToCollectPuck()
{
	return m_field.getTargetsForCollectingOnePuck(m_field.getOwnTeamColor());
}

FieldColor DrivePuckToAchiveGoals::getColorOfTargetPucks()
{
	return m_field.getOwnTeamColor();
}

unsigned int DrivePuckToAchiveGoals::getNumberOfKnownPucksNotInTarget()
{
	return 0;
}

