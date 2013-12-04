#include "layer/strategy/refereemock.h"

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
    return false;
}

bool RefereeMock::gameStart()
{
    return false;
}

bool RefereeMock::gameOver()
{
    return false;
}

Extern::Angelina::TeamColor RefereeMock::trueColorOfTeam()
{
    return blue;
}

bool RefereeMock::stopMovement()
{
    return false;
}

bool RefereeMock::isValid()
{
    return true;
}























