#include "layer/hardware/engineimpl.h"

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
	m_engine(playerClient, 0)
{
}

void EngineImpl::setSpeed(double /*magnitude*/, double /*rotation*/)
{
}
