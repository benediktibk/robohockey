#include "common/watchmock.h"

using namespace RoboHockey::Common;

WatchMock::WatchMock() :
	m_time(0)
{ }

double WatchMock::getTimeAndRestart()
{
	return m_time;
}

double WatchMock::getTime() const
{
	return m_time;
}

void WatchMock::setTime(double time)
{
	m_time = time;
}

