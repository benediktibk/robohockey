#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;
using namespace PlayerCc;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
    m_engine(new Position2dProxy(playerClient, 0)),
    m_posX(m_engine->GetXPos()),
    m_posY(m_engine->GetYPos()),
    m_orientation(m_angle.getOrientation())

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

bool EngineImpl::isMoving()
{
    Compare compare(0.00000001);
    m_orientation_equal = compare.isFuzzyEqual(m_angle.getOrientation(), m_orientation);
    m_posX_equal = compare.isFuzzyEqual(m_engine->GetXPos(), m_posX);
    m_posY_equal = compare.isFuzzyEqual(m_engine->GetYPos(), m_posY);
    m_posX = m_engine->GetXPos();
    m_posY = m_engine->GetYPos();
    m_orientation = m_angle.getOrientation();
    if(m_orientation_equal && m_posX_equal && m_posY_equal)
    {
        m_posX = m_engine->GetXPos();
        m_posY = m_engine->GetYPos();
        m_orientation = m_angle.getOrientation();
        return false;
    }
    m_posX = m_engine->GetXPos();
    m_posY = m_engine->GetYPos();
    m_orientation = m_angle.getOrientation();
    return true;
    //return (m_engine->GetXSpeed() != 0) && (m_engine->GetYawSpeed() != 0);
}

double EngineImpl::getSpeed() const
{
	return m_engine->GetXSpeed();
}

EngineImpl::EngineImpl(const EngineImpl &)
{ }

void EngineImpl::operator=(const EngineImpl &)
{ }
