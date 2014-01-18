#include "common/watchimpl.h"
#include <sys/time.h>
#include <assert.h>

using namespace RoboHockey::Common;

WatchImpl::WatchImpl() :
	m_initialTime(getCurrentAbsoluteTime())
{ }

double WatchImpl::getTime() const
{
	double totalTime = getCurrentAbsoluteTime();
	double timeDifference = totalTime - m_initialTime;
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
