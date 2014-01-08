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

		virtual double getTime() const;

		void setTime(double time);

	private:
		double m_time;
	};
}
}

#endif


