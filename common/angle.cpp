#include "common/angle.h"
#include "common/point.h"
#include "common/compare.h"
#include <math.h>
#include <assert.h>

using namespace RoboHockey::Common;
using namespace std;

Angle::Angle() :
	m_value(0)
{ }

Angle::Angle(double value) :
	m_value(value)
{
	fixRange();
}

Angle::Angle(const Point &source, const Point &targetOne, const Point &targetTwo)
{
	double a = source.distanceTo(targetOne);
	double b = source.distanceTo(targetTwo);
	double c = targetOne.distanceTo(targetTwo);
	Compare compare(0.001);

	if (compare.isFuzzyEqual(a, 0) || compare.isFuzzyEqual(b, 0))
		m_value = 0;
	else
	{
		double numerator = a*a + b*b - c*c;
		double denominator = 2*a*b;
		m_value = acos(numerator/denominator);
	}

	fixRange();
}

Angle::Angle(const Point &start, const Point &end)
{
	Point positionDifference = end - start;
	m_value = atan2(positionDifference.getY(), positionDifference.getX());
	fixRange();
}

double Angle::getValueBetweenMinusPiAndPi() const
{
	return m_value;
}

double Angle::getValueBetweenZeroAndTwoPi() const
{
	double value = m_value;

	if (value < 0)
		value += 2*M_PI;

	return value;
}

Angle Angle::operator+(const Angle &rhs) const
{
	return Angle(getValueBetweenMinusPiAndPi() + rhs.getValueBetweenMinusPiAndPi());
}

Angle Angle::operator-(const Angle &rhs) const
{
	return Angle(getValueBetweenMinusPiAndPi() - rhs.getValueBetweenMinusPiAndPi());
}

Angle Angle::getHalfRotation()
{
	return Angle(M_PI);
}

Angle Angle::getQuarterRotation()
{
	return Angle(M_PI/2);
}

Angle Angle::getFullRotation()
{
	return Angle(0);
}

void Angle::fixRange()
{
	while (m_value <= M_PI)
		m_value += 2*M_PI;

	unsigned int timesTooMuch = m_value/(2*M_PI);
	m_value -= 2*M_PI*timesTooMuch;

	if (m_value > M_PI)
		m_value -= 2*M_PI;
}

ostream &operator<<(ostream &stream, const Angle &angle)
{
	stream << angle.getValueBetweenMinusPiAndPi();
	return stream;
}
