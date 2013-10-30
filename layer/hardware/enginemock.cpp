#include "layer/hardware/enginemock.h"

using namespace RoboHockey::Layer::Hardware;

EngineMock::EngineMock() :
	m_callsToSetSpeed(0)
{ }

void EngineMock::setSpeed(double, double)
{
	++m_callsToSetSpeed;
}

unsigned int EngineMock::getCallsToSetSpeed() const
{
	return m_callsToSetSpeed;
}
