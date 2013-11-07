#include "layer/dataanalysis/enginemock.h"

using namespace RoboHockey::Layer::DataAnalysis;

EngineMock::EngineMock() :
	m_callsToGoToStraight(0)
{ }

void EngineMock::goToStraight(const Common::Point &)
{
	++m_callsToGoToStraight;
}

void EngineMock::updateSpeedAndMagnitude()
{ }

void EngineMock::stop()
{ }

unsigned int EngineMock::getCallsToGoToStraight() const
{
	return m_callsToGoToStraight;
}


