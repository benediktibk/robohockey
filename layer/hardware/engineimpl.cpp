#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
	m_engine(new Position2dProxy(playerClient, 0))
{
}

EngineImpl::~EngineImpl()
{
	delete m_engine;
}

void EngineImpl::setSpeed(double magnitude, double rotation)
{
	return m_engine->SetSpeed(magnitude, rotation);
}
