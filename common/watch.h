#ifndef ROBOHOCKEY_COMMON_WATCH_H
#define ROBOHOCKEY_COMMON_WATCH_H

namespace RoboHockey
{
namespace Common
{
	class Watch
	{
	public:
		Watch();

		double getTimeAndRestart();

	private:
		double getCurrentAbsoluteTime() const;

	private:
		double m_lastTime;
	};
}
}

#endif
