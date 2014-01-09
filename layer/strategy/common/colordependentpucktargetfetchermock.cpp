#include "layer/strategy/common/colordependentpucktargetfetchermock.h"
#include "common/robotposition.h"
#include "common/fieldcolor.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace std;
using namespace RoboHockey::Common;

ColorDependentPuckTargetFetcherMock::ColorDependentPuckTargetFetcherMock() :
	m_numberOfKnownPucksNotInTarget(0),
	m_isAchievingGoals(false)
{ }

list<RobotPosition> ColorDependentPuckTargetFetcherMock::getTargetPositions() const
{
	return m_targetPositions;
}

list<RobotPosition> ColorDependentPuckTargetFetcherMock::getPositionsToCollectPuck() const
{
	return list<RobotPosition>();
}

FieldColor ColorDependentPuckTargetFetcherMock::getColorOfTargetPucks() const
{
	return FieldColorUnknown;
}

unsigned int ColorDependentPuckTargetFetcherMock::getNumberOfKnownPucksNotInTarget() const
{
	return m_numberOfKnownPucksNotInTarget;
}

bool ColorDependentPuckTargetFetcherMock::isAchievingGoals() const
{
	return m_isAchievingGoals;
}

void ColorDependentPuckTargetFetcherMock::setNumberOfKnownPucksNotInTarget(unsigned int value)
{
	m_numberOfKnownPucksNotInTarget = value;
}

void ColorDependentPuckTargetFetcherMock::setTargetPositions(const list<RobotPosition> &positions)
{
	m_targetPositions = positions;
}

void ColorDependentPuckTargetFetcherMock::setisAchievingGoals(bool value)
{
	m_isAchievingGoals = value;
}
