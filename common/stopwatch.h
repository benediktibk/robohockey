#ifndef ROBOHOCKEY_COMMON_STOPWATCH_H
#define ROBOHOCKEY_COMMON_STOPWATCH_H

namespace RoboHockey
{
namespace Common
{
	class Watch;

	class StopWatch
	{
	public:
		StopWatch(const Watch &watch);

		double getTimeAndRestart();

	private:
		const Watch &m_watch;
		double m_startTime;
	};
}
}

#endif


