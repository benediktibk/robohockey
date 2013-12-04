#include "watch.h"
#include <sys/time.h>
#include <sys/resource.h>

using namespace RoboHockey::Common;

Watch::Watch()
{ }

double Watch::getTimeAndRestart()
{
	rusage usage;
	getrusage(RUSAGE_SELF, &usage);
	timeval usrTime = usage.ru_utime;
	timeval sysTime = usage.ru_stime;
	double usrTimeTotal = usrTime.tv_sec + usrTime.tv_usec/static_cast<double>(1E6);
	double sysTimeTotal = sysTime.tv_sec + sysTime.tv_usec/static_cast<double>(1E6);
	return sysTimeTotal + usrTimeTotal;
}
