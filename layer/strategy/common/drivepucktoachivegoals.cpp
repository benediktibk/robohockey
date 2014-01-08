#include "layer/strategy/common/drivepucktoachivegoals.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

DrivePuckToAchiveGoals::DrivePuckToAchiveGoals(const Field &field) :
	m_field(field)
{ }

list<RobotPosition> DrivePuckToAchiveGoals::getTargetPositions() const
{
	return m_field.getTargetsForScoringGoals();
}

list<RobotPosition> DrivePuckToAchiveGoals::getPositionsToCollectPuck() const
{
	return m_field.getTargetsForCollectingOnePuck(getColorOfTargetPucks());
}

FieldColor DrivePuckToAchiveGoals::getColorOfTargetPucks() const
{
	return m_field.getOwnTeamColor();
}

unsigned int DrivePuckToAchiveGoals::getNumberOfKnownPucksNotInTarget() const
{
	return m_field.getNumberOfObjectsWithColor(getColorOfTargetPucks()) - m_field.getNumberOfAchievedGoals();
}

