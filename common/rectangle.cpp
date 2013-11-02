#include "common/rectangle.h"
#include "common/compare.h"
#include <algorithm>

using namespace RoboHockey::Common;
using namespace std;

Rectangle::Rectangle(const Point &one, const Point &two) :
	m_leftLower(min(one.getX(), two.getX()), min(one.getY(), two.getY())),
	m_rightUpper(max(one.getX(), two.getX()), max(one.getY(), two.getY()))
{ }

const Point &Rectangle::getLeftLower() const
{
	return m_leftLower;
}

const Point &Rectangle::getRightUpper() const
{
	return m_rightUpper;
}

bool Rectangle::isInside(const Point &point, const Compare &compare) const
{
	return	compare.isFuzzyGreater(point.getX(), m_leftLower.getX()) &&
			compare.isFuzzyGreater(point.getY(), m_leftLower.getY()) &&
			compare.isFuzzySmaller(point.getX(), m_rightUpper.getX()) &&
			compare.isFuzzySmaller(point.getY(), m_rightUpper.getY());
}
