#include "common/watchimpl.h"
#include <sys/time.h>
#include <assert.h>

using namespace RoboHockey::Common;

WatchImpl::WatchImpl() :
	m_lastTime(getCurrentAbsoluteTime())
{ }

double WatchImpl::getTimeAndRestart()
{
	double totalTime = getCurrentAbsoluteTime();
	double timeDifference = totalTime - m_lastTime;
	m_lastTime = totalTime;
	return timeDifference;
}

double WatchImpl::getTime() const
{
	double totalTime = getCurrentAbsoluteTime();
	double timeDifference = totalTime - m_lastTime;
	return timeDifference;
}

double WatchImpl::getCurrentAbsoluteTime() const
{
	timeval timeStructure;
	int errorCode = gettimeofday(&timeStructure, 0);
	assert(errorCode == 0);
	(void)(errorCode); // avoid errors in release build
	double seconds = timeStructure.tv_sec;
	double microSeconds = timeStructure.tv_usec;
	double totalTime = seconds + microSeconds/1E6;
	return totalTime;
}
