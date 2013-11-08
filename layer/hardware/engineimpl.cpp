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
	delete m_engine;
	m_engine = 0;
}

void EngineImpl::setSpeed(double magnitude, double rotation)
{
	// tresholds for the speed magnitude
	if (magnitude > 0.5)
		magnitude = 0.5;
	else if (magnitude < -0.5)
		magnitude = -0.5;

	// tresholds for the rotation
	if (rotation > M_PI)
		rotation = M_PI;
	else if (rotation < (-1)*M_PI)
		rotation = (-1)*M_PI;

	return m_engine->SetSpeed(magnitude, rotation);
}

EngineImpl::EngineImpl(const EngineImpl &)
{ }

void EngineImpl::operator=(const EngineImpl &)
{ }
