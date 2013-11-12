#include "layer/hardware/engine.h"
#include <math.h>

using namespace RoboHockey::Layer::Hardware;

// physical maximum is something around 0.5 m/s
const double Engine::m_maximumMagnitude = 0.3;
const double Engine::m_minimumMagnitude = 0.001;
// physical maximum is something around pi rad/s
const double Engine::m_maximumRotation = M_PI;
const double Engine::m_minimumRotation = 0.1;


double Engine::getMaximumRotation() const
{
	return m_maximumRotation;
}

double Engine::getMaximumSpeed() const
{
	return m_maximumMagnitude;
}

double Engine::getMinimumRotation() const
{
	return m_minimumRotation;
}

double Engine::getMinimumSpeed() const
{
	return m_minimumMagnitude;
}
