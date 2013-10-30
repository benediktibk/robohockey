#include "layer/hardware/engineimpl.h"
#include <player-3.0/libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
	m_engine(new Position2dProxy(playerClient, 0))
{
}

void EngineImpl::setSpeed(double magnitude, double rotation)
{
	return m_engine->SetSpeed(magnitude, rotation);
}
