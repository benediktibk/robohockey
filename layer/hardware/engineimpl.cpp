#include "layer/hardware/engineimpl.h"
#include <libplayerc++/playerc++.h>
#include <fstream>

using namespace RoboHockey::Layer::Hardware;
using namespace RoboHockey::Common;
using namespace PlayerCc;
using namespace std;

EngineImpl::EngineImpl(PlayerCc::PlayerClient *playerClient) :
	m_engine(new Position2dProxy(playerClient, 0)),
	m_lastXPos(m_engine->GetXPos()),
	m_lastYPos(m_engine->GetYPos()),
	m_lastOrientation(m_engine->GetYaw()),
	m_currentXPos(m_engine->GetXPos()),
	m_currentYPos(m_engine->GetYPos()),
	m_currentOrientation(m_engine->GetYaw()),
	m_enabled(false)
{
	m_engine->SetMotorEnable(true);
	setSpeed(0, 0);
}

EngineImpl::~EngineImpl()
{
	setSpeed(0, 0);
	setEnabled(false);
	delete m_engine;
	m_engine = 0;
}

void EngineImpl::setSpeed(double magnitude, double rotation)
{
	m_engine->SetSpeed(magnitude, rotation);
}

bool EngineImpl::isMoving() const
{
	Compare compare(0.001);

	return	!compare.isFuzzyEqual(m_currentOrientation, m_lastOrientation) &&
			!compare.isFuzzyEqual(m_currentXPos, m_lastXPos) &&
			!compare.isFuzzyEqual(m_currentYPos, m_lastYPos);
}

double EngineImpl::getSpeed() const
{
	return m_engine->GetXSpeed();
}

void EngineImpl::setEnabled(bool value)
{
	if (m_enabled != value)
		m_engine->SetMotorEnable(value);
	m_enabled = value;
}

void EngineImpl::writeDataToFile(const string &fileName) const
{
	fstream file(fileName.c_str(), ios_base::out | ios_base::trunc);

	file << isMoving() << endl;
	file << getSpeed() << endl;

	file.close();
}

void EngineImpl::updateSensorData()
{
	m_lastXPos = m_currentXPos;
	m_lastYPos = m_currentYPos;
	m_lastOrientation = m_currentOrientation;
	m_currentXPos = m_engine->GetXPos();
	m_currentYPos = m_engine->GetYPos();
	m_currentOrientation = m_engine->GetYaw();
}

EngineImpl::EngineImpl(const EngineImpl &)
{ }

void EngineImpl::operator=(const EngineImpl &)
{ }
