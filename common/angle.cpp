#include "common/angle.h"
#include <math.h>

using namespace RoboHockey::Common;

Angle::Angle() :
	m_value(0)
{ }

Angle::Angle(double value) :
	m_value(value)
{
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
