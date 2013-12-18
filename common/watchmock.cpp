#include "common/watchmock.h"

using namespace RoboHockey::Common;

WatchMock::WatchMock() :
	m_time(0),
	m_callsToGetTimeAndRestart(0)
{ }

double WatchMock::getTimeAndRestart()
{
	++m_callsToGetTimeAndRestart;
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

unsigned int WatchMock::getCallsToGetTimeAndRestart() const
{
	return m_callsToGetTimeAndRestart;
}

