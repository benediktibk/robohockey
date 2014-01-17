#include "common/compare.h"
#include "common/point.h"
#include "common/circle.h"
#include "common/robotposition.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace std;

Compare::Compare(double epsilon) :
	m_epsilon(epsilon)
{ }

bool Compare::isFuzzyEqual(double value1, double value2) const
{
	return fabs(value1 - value2) < m_epsilon;
}

bool Compare::isFuzzyEqual(const Angle &one, const Angle &two) const
{
	return	isFuzzyEqual(one.getValueBetweenMinusPiAndPi(), two.getValueBetweenMinusPiAndPi()) ||
			isFuzzyEqual(one.getValueBetweenZeroAndTwoPi(), two.getValueBetweenZeroAndTwoPi());
}

bool Compare::isFuzzyEqual(const vector<double> &one, const vector<double> &two) const
{
	if (one.size() != two.size())
		return false;

	for (size_t i = 0; i < one.size(); ++i)
		if (!isFuzzyEqual(one[i], two[i]))
			return false;

	return true;
}

bool Compare::isFuzzyEqual(const Point &one, const Point &two) const
{
	return	isFuzzyEqual(one.getX(), two.getX()) &&
			isFuzzyEqual(one.getY(), two.getY());
}

bool Compare::isFuzzyEqual(const Circle &one, const Circle &two) const
{
	return	isFuzzyEqual(one.getCenter(), two.getCenter()) &&
			isFuzzyEqual(one.getDiameter(), two.getDiameter());
}

bool Compare::isFuzzyEqual(const RobotPosition &one, const RobotPosition &two) const
{
	return	isFuzzyEqual(one.getPosition(), two.getPosition()) &&
			isFuzzyEqual(one.getOrientation(), two.getOrientation());
}

bool Compare::isFuzzyEqual(const list<RobotPosition> &one, const list<RobotPosition> &two) const
{
	list<RobotPosition>::const_iterator j = two.begin();
	if(one.size() != two.size())
		return false;

	for(list<RobotPosition>::const_iterator i = one.begin(); i != one.end(); ++i, ++j)
		if(!isFuzzyEqual((*i), (*j)))
			return false;

	return true;
}

bool Compare::isFuzzyGreater(double value1, double value2) const
{
	return value1 + m_epsilon > value2;
}

bool Compare::isFuzzySmaller(double value1, double value2) const
{
	return value1 < m_epsilon + value2;
}

bool Compare::isStrictFuzzyGreater(double value1, double value2) const
{
	return value1 > m_epsilon + value2;
}

bool Compare::isStrictFuzzySmaller(double value1, double value2) const
{
	return value1 + m_epsilon < value2;
}
