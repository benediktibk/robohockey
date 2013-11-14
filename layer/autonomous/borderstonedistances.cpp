#include "layer/autonomous/borderstonedistances.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

BorderStoneDistances::BorderStoneDistances():
	m_compare(new Compare(0.02))
{ }

BorderStoneDistances::~BorderStoneDistances()
{
	delete m_compare;
	m_compare = 0;
}

double BorderStoneDistances::getStandardFieldDistance(BorderStoneFieldDistance distanceType) const
{
	double result = 0.0;

	switch (distanceType)
	{
		case BorderStoneFieldDistanceA:
			result = 5.0 / 12.0;
			break;

		case BorderStoneFieldDistanceB:
			result = 15.0 / 12.0;
			break;

		case BorderStoneFieldDistanceC:
			result = 5.0 / 6.0;
			break;

		case BorderStoneFieldDistanceD:
			result = 3.0;
			break;

		default:
			result = 0.0;
			break;
	}

	return result;
}

bool BorderStoneDistances::distanceIsStandardDistance(double distance) const
{
	for (int i = BorderStoneFieldDistanceA; i <= BorderStoneFieldDistanceD; ++i)
		if (m_compare->isFuzzyEqual(distance, getStandardFieldDistance(static_cast<BorderStoneFieldDistance>(i))))
			return true;

	return false;
}

BorderStoneFieldDistance BorderStoneDistances::checkForStandardDistance(double distance) const
{
	for (int i = BorderStoneFieldDistanceA; i != BorderStoneFieldDistanceD; i++)
		if (m_compare->isFuzzyEqual(distance, getStandardFieldDistance(static_cast<BorderStoneFieldDistance>(i))))
			return static_cast<BorderStoneFieldDistance>(i);

	return BorderStoneFieldDistanceFalse;
}
