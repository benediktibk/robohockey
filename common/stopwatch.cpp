#include "common/stopwatch.h"
#include "common/watch.h"

using namespace RoboHockey::Common;

StopWatch::StopWatch(const Watch &watch) :
	m_watch(watch),
	m_startTime(watch.getTime())
{ }

double StopWatch::getTimeAndRestart()
{
	double time = m_watch.getTime();
	double timeDifference = time - m_startTime;
	m_startTime = time;
	return timeDifference;
}

double StopWatch::getTime() const
{
	double time = m_watch.getTime();
	return time - m_startTime;
}

