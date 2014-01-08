#include "layer/strategy/common/drivepuckmock.h"
#include "common/robotposition.h"
#include "common/fieldcolor.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace std;
using namespace RoboHockey::Common;

DrivePuckMock::DrivePuckMock() :
	m_numberOfKnownPucksNotInTarget(0)
{ }

list<RobotPosition> DrivePuckMock::getTargetPositions() const
{
	return list<RobotPosition>();
}

list<RobotPosition> DrivePuckMock::getPositionsToCollectPuck() const
{
	return list<RobotPosition>();
}

FieldColor DrivePuckMock::getColorOfTargetPucks() const
{
	return FieldColorUnknown;
}

unsigned int DrivePuckMock::getNumberOfKnownPucksNotInTarget() const
{
	return m_numberOfKnownPucksNotInTarget;
}

void DrivePuckMock::setNumberOfKnownPucksNotInTarget(unsigned int value)
{
	m_numberOfKnownPucksNotInTarget = value;
}
