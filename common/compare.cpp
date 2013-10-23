#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;

Compare::Compare(double epsilon) :
	m_epsilon(epsilon)
{ }

bool Compare::isFuzzyEqual(double value1, double value2)
{
	if(fabs(value1 - value2) < m_epsilon)
		return true;
	else
		return false;
}

bool Compare::isFuzzyGreater(double value1, double value2)
{
	if(value1 + m_epsilon > value2)
		return true;
	else
		return false;
}

bool Compare::isFuzzySmaller(double value1, double value2)
{
	if(value1 < m_epsilon + value2)
		return true;
	else
		return false;
}

bool Compare::isStrictFuzzyGreater(double value1, double value2)
{
	if(value1 > m_epsilon + value2)
		return true;
	else
		return false;
}

bool Compare::isStrictFuzzySmaller(double value1, double value2)
{
	if(value1 + m_epsilon < value2)
		return true;
	else
		return false;
}
