#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
	m_engine(new Position2dProxy(playerClient, 0))
{
	setSpeed(0, 0);
}

EngineImpl::~EngineImpl()
{
	setSpeed(0, 0);
	delete m_engine;
	m_engine = 0;
}

void EngineImpl::setSpeed(double magnitude, double rotation)
{
	bool enableMotor = false;
	if (magnitude != 0 || rotation != 0)
		enableMotor = true;

	m_engine->SetMotorEnable(enableMotor);
	m_engine->SetSpeed(magnitude, rotation);
}

bool EngineImpl::isMoving() const
{
	return (m_engine->GetXSpeed() != 0) && (m_engine->GetYawSpeed() != 0);
}

EngineImpl::EngineImpl(const EngineImpl &)
{ }

void EngineImpl::operator=(const EngineImpl &)
{ }
