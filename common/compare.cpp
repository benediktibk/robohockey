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
	if(fabs(value1 - value2) < m_epsilon)
		return true;
	else
		return false;
}

bool Compare::isFuzzyEqual(const Angle &one, const Angle &two) const
{
	return isFuzzyEqual(one.getValueBetweenMinusPiAndPi(), two.getValueBetweenMinusPiAndPi());
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
	size_t size1, size2;
	size1 = one.size();
	size2 = two.size();
	list<RobotPosition>::const_iterator j = two.begin();
	if(size1 != size2)
		return false;
	for(list<RobotPosition>::const_iterator i = one.begin(); i != one.end(); ++i, ++j)
	{
		const RobotPosition &robotPosition1 = *i;
		const RobotPosition &robotPosition2 = *j;
		if(!isFuzzyEqual(robotPosition1, robotPosition2))
			return false;
	}
	return true;
}

bool Compare::isFuzzyGreater(double value1, double value2) const
{
	if(value1 + m_epsilon > value2)
		return true;
	else
		return false;
}

bool Compare::isFuzzySmaller(double value1, double value2) const
{
	if(value1 < m_epsilon + value2)
		return true;
	else
		return false;
}

bool Compare::isStrictFuzzyGreater(double value1, double value2) const
{
	if(value1 > m_epsilon + value2)
		return true;
	else
		return false;
}

bool Compare::isStrictFuzzySmaller(double value1, double value2) const
{
	if(value1 + m_epsilon < value2)
		return true;
	else
		return false;
}
