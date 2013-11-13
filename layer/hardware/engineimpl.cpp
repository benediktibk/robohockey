#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
	m_engine(new Position2dProxy(playerClient, 0))
{
	m_engine->SetMotorEnable(true);
}

EngineImpl::~EngineImpl()
{
	setSpeed(0, 0);
	delete m_engine;
	m_engine = 0;
}

void EngineImpl::setSpeed(double magnitude, double rotation)
{
	magnitude = limitToTresholds(magnitude, getMinimumSpeed(), getMaximumSpeed());
	rotation = limitToTresholds(rotation, getMinimumRotation(), getMaximumRotation());
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
