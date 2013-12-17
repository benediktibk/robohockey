#ifndef ROBOHOCKEY_COMMON_WATCHMOCK_H
#define ROBOHOCKEY_COMMON_WATCHMOCK_H

#include "common/watch.h"

namespace RoboHockey
{
namespace Common
{
	class WatchMock :
			public Watch
	{
	public:
		WatchMock();

		virtual double getTimeAndRestart();
		virtual double getTime() const;

		void setTime(double time);
		unsigned int getCallsToGetTimeAndRestart() const;

	private:
		double m_time;
		unsigned int m_callsToGetTimeAndRestart;
	};
}
}

#endif


