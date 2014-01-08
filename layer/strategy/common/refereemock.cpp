#include "layer/strategy/common/refereemock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace Extern::Angelina;

RefereeMock::RefereeMock() :
	m_detectionStart(false),
	m_gameStart(false),
	m_gameOver(false),
	m_stopMovement(false),
	m_trueColor(FieldColorUnknown)
{ }

void RefereeMock::reportReady()
{ }

void RefereeMock::reportDone()
{ }

void RefereeMock::sendAlive()
{ }

void RefereeMock::tellTeamColor(RoboHockey::Common::FieldColor)
{ }

void RefereeMock::reportGoal()
{ }

void RefereeMock::tellEgoPos(const RoboHockey::Common::Point &)
{ }

bool RefereeMock::detectionStart()
{
	return m_detectionStart;
}

bool RefereeMock::gameStart()
{
	return m_gameStart;
}

bool RefereeMock::gameOver()
{
	return m_gameOver;
}

RoboHockey::Common::FieldColor RefereeMock::trueColorOfTeam()
{
	return m_trueColor;
}

bool RefereeMock::stopMovement()
{
	return m_stopMovement;
}

bool RefereeMock::isValid()
{
	return true;
}

void RefereeMock::setDetectionStart(bool value)
{
	m_detectionStart = value;
}

void RefereeMock::setGameStart(bool value)
{
	m_gameStart = value;
}

void RefereeMock::setGameOver(bool value)
{
	m_gameOver = value;
}

void RefereeMock::setStopMovement(bool value)
{
	m_stopMovement = value;
}

void RefereeMock::setTrueColorOfTeam(FieldColor color)
{
	m_trueColor = color;
}
