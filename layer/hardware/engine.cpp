#include "layer/hardware/engine.h"
#include <math.h>

using namespace RoboHockey::Layer::Hardware;

/*!
 * the physical maximum is something around 0.5 m/s
 */
const double Engine::m_maximumMagnitude = 0.3;
const double Engine::m_minimumMagnitude = 0.001;
/*!
 * the physical maximum is something around pi rad/s
 */
const double Engine::m_maximumRotation = M_PI;
/*!
 * Actually this value would be something around pi/25, but
 * only if the robot is not moving at all. If the robot
 * moves forward smaller rotation speeds are possible.
 **/
const double Engine::m_minimumRotation = 0;

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
