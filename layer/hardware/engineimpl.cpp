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
	m_engine->SetMotorEnable(false);
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

	// minimum tresholds
	if (fabs(rotation) < 0.1)
		rotation = 0;
	if (fabs(magnitude) < 0.001)
		magnitude = 0;

	std::cout << "magnitude: " << magnitude << ", rotation: " << rotation << std::endl;

	return m_engine->SetSpeed(magnitude, rotation);
}

EngineImpl::EngineImpl(const EngineImpl &)
{ }

void EngineImpl::operator=(const EngineImpl &)
{ }
