#include "layer/strategy/common/drivepuckmock.h"
#include "common/robotposition.h"
#include "common/fieldcolor.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace std;
using namespace RoboHockey::Common;

DrivePuckMock::DrivePuckMock() :
	m_numberOfKnownPucksNotInTarget(0)
{
}

std::list<RoboHockey::Common::RobotPosition> DrivePuckMock::getTargetPositions()
{
	return list<RobotPosition>;
}

std::list<RobotPosition> DrivePuckMock::getPositionsToCollectPuck()
{
	return list<RobotPosition>;
}

FieldColor DrivePuckMock::getColorOfTargetPucks()
{
	return FieldColorUnknown;
}

unsigned int DrivePuckMock::getNumberOfKnownPucksNotInTarget()
{
	return m_numberOfKnownPucksNotInTarget;
}

void DrivePuckMock::setNumberOfKnownPucksNotInTarget(unsigned int value)
{
	m_numberOfKnownPucksNotInTarget = value;
}
