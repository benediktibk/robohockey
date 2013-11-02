#include "common/rectangle.h"
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
