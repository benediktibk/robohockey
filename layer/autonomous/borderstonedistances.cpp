#include "layer/autonomous/borderstonedistances.h"
#include "common/compare.h"
#include "common/point.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

BorderStoneDistances::BorderStoneDistances(double epsilon):
	m_compare(epsilon)
{ }

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

	case BorderStoneFieldDistanceRoot:
	case BorderStoneFieldDistanceFalse:
		result = 0.0;
		break;
	}

	return result;
}

bool BorderStoneDistances::isDistanceStandardDistance(double distance) const
{
	for (int i = BorderStoneFieldDistanceA; i <= BorderStoneFieldDistanceD; ++i)
		if (m_compare.isFuzzyEqual(distance, getStandardFieldDistance(static_cast<BorderStoneFieldDistance>(i))))
			return true;

	return false;
}

BorderStoneFieldDistance BorderStoneDistances::getStandardDistanceType(double distance) const
{
	for (int i = BorderStoneFieldDistanceA; i != BorderStoneFieldDistanceD; i++)
		if (m_compare.isFuzzyEqual(distance, getStandardFieldDistance(static_cast<BorderStoneFieldDistance>(i))))
			return static_cast<BorderStoneFieldDistance>(i);

	return BorderStoneFieldDistanceFalse;
}

bool BorderStoneDistances::verifyPoints(vector<Point> &points)
{
	unsigned int numberOfA = 0;
	unsigned int numberOfB = 0;
	unsigned int numberOfC = 0;

	Point lastPoint = points.front();
	BorderStoneFieldDistance lastDistance = BorderStoneFieldDistanceFalse;

	if (points.size() < (size_t) 3 || points.size() > (size_t) 7)
		return false;

	for (vector<Point>::const_iterator it = points.begin() + 1; it != points.end(); ++it)
	{
		BorderStoneFieldDistance currentDistance = getStandardDistanceType(lastPoint.distanceTo(*it));

		if (currentDistance == BorderStoneFieldDistanceFalse || currentDistance == BorderStoneFieldDistanceD
				|| currentDistance == BorderStoneFieldDistanceRoot)
			return false;

		if (currentDistance == lastDistance && (currentDistance == BorderStoneFieldDistanceA || currentDistance == BorderStoneFieldDistanceB))
			return false;

		if (currentDistance == BorderStoneFieldDistanceC && lastDistance != BorderStoneFieldDistanceC && numberOfC > 0)
			return false;

		if (currentDistance == BorderStoneFieldDistanceA && numberOfA > 0 && (numberOfB != 2 || numberOfC != 2))
			return false;

		if (currentDistance == BorderStoneFieldDistanceB && numberOfB > 0 && numberOfC != 2)
			return false;

		if (currentDistance == BorderStoneFieldDistanceA)
			++numberOfA;
		else if (currentDistance == BorderStoneFieldDistanceB)
			++numberOfB;
		else if (currentDistance == BorderStoneFieldDistanceC)
			++numberOfC;

		lastPoint = (*it);
		lastDistance = currentDistance;
	}

	if (numberOfA > 2 || numberOfB > 2 || numberOfC > 2)
		return false;

	return true;
}
