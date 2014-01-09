#include "layer/strategy/common/colordependendpucktargetfetchermock.h"
#include "common/robotposition.h"
#include "common/fieldcolor.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace std;
using namespace RoboHockey::Common;

ColorDependendPuckTargetFetcherMock::ColorDependendPuckTargetFetcherMock() :
	m_numberOfKnownPucksNotInTarget(0)
{ }

list<RobotPosition> ColorDependendPuckTargetFetcherMock::getTargetPositions() const
{
	return list<RobotPosition>();
}

list<RobotPosition> ColorDependendPuckTargetFetcherMock::getPositionsToCollectPuck() const
{
	return list<RobotPosition>();
}

FieldColor ColorDependendPuckTargetFetcherMock::getColorOfTargetPucks() const
{
	return FieldColorUnknown;
}

unsigned int ColorDependendPuckTargetFetcherMock::getNumberOfKnownPucksNotInTarget() const
{
	return m_numberOfKnownPucksNotInTarget;
}

void ColorDependendPuckTargetFetcherMock::setNumberOfKnownPucksNotInTarget(unsigned int value)
{
	m_numberOfKnownPucksNotInTarget = value;
}
