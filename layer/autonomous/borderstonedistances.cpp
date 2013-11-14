#include "layer/autonomous/borderstonedistances.h"

using namespace RoboHockey::Layer::Autonomous;

BorderStoneDistances::BorderStoneDistances()
{ }

double BorderStoneDistances::getStandardFieldDistance(BorderStoneFieldDistance /*distanceType*/) const
{
	return 0.0;
}

BorderStoneFieldDistance BorderStoneDistances::checkForStandardDistance() const
{
	return BorderStoneFieldDistanceFalse;
}
