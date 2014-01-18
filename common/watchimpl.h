#ifndef ROBOHOCKEY_COMMON_WATCHIMPL_H
#define ROBOHOCKEY_COMMON_WATCHIMPL_H

#include "common/watch.h"

namespace RoboHockey
{
namespace Common
{
	class WatchImpl :
			public Watch
	{
	public:
		WatchImpl();

		virtual double getTime() const;

	private:
		double getCurrentAbsoluteTime() const;

	private:
		double m_initialTime;
	};
}
}

#endif
