#include "layer/autonomous/routelengthcompare.h"
#include "layer/autonomous/route.h"

using namespace RoboHockey::Layer::Autonomous;

RouteLengthCompare::RouteLengthCompare()
{ }

bool RouteLengthCompare::operator()(const Route &one, const Route &two) const
{
	return one.getLength() < two.getLength();
}

