#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

// physical maximum is something around 0.5 m/s
const double EngineImpl::m_maximumMagnitude = 0.3;
const double EngineImpl::m_minimumMagnitude = 0.001;
// physical maximum is something around pi rad/s
const double EngineImpl::m_maximumRotation = M_PI;
const double EngineImpl::m_minimumRotation = 0.1;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
	m_engine(new Position2dProxy(playerClient, 0))
{
	m_engine->SetMotorEnable(true);
}

EngineImpl::~EngineImpl()
{
	setSpeed(0, 0);
	m_engine->SetMotorEnable(false);
	delete m_engine;
	m_engine = 0;
}

void EngineImpl::setSpeed(double magnitude, double rotation)
{
	magnitude = limitToTresholds(magnitude, m_minimumMagnitude, m_maximumMagnitude);
	rotation = limitToTresholds(rotation, m_minimumRotation, m_maximumRotation);
	return m_engine->SetSpeed(magnitude, rotation);
}

double EngineImpl::limitToTresholds(double value, double lowerBound, double upperBound) const
{
	if (value > upperBound)
		value = upperBound;
	else if (value < (-1)*upperBound)
		value = (-1)*upperBound;

	if (fabs(value) < lowerBound)
		value = 0;

	return value;
}

EngineImpl::EngineImpl(const EngineImpl &)
{ }

void EngineImpl::operator=(const EngineImpl &)
{ }
