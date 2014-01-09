#include "layer/strategy/common/colordependentpucktargetfetchermock.h"
#include "common/robotposition.h"
#include "common/fieldcolor.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace std;
using namespace RoboHockey::Common;

ColorDependentPuckTargetFetcherMock::ColorDependentPuckTargetFetcherMock() :
	m_numberOfKnownPucksNotInTarget(0)
{ }

list<RobotPosition> ColorDependentPuckTargetFetcherMock::getTargetPositions() const
{
	return list<RobotPosition>();
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

void ColorDependentPuckTargetFetcherMock::setNumberOfKnownPucksNotInTarget(unsigned int value)
{
	m_numberOfKnownPucksNotInTarget = value;
}