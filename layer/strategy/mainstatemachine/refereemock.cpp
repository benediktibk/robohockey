#include "layer/strategy/mainstatemachine/refereemock.h"

using namespace RoboHockey::Layer::Strategy;
using namespace Extern::Angelina;

RefereeMock::RefereeMock()
{ }

void RefereeMock::reportReady()
{
}

void RefereeMock::reportDone()
{
}

void RefereeMock::sendAlive()
{
}

void RefereeMock::tellTeamColor(Extern::Angelina::TeamColor)
{
}

void RefereeMock::reportGoal()
{
}

void RefereeMock::tellEgoPos(const RoboHockey::Common::Point &)
{
}

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

Extern::Angelina::TeamColor RefereeMock::trueColorOfTeam()
{
    return blue;
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

























