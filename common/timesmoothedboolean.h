#ifndef ROBOHOCKEY_COMMON_TIMESMOOTHEDBOOLEAN_H
#define ROBOHOCKEY_COMMON_TIMESMOOTHEDBOOLEAN_H

namespace RoboHockey
{
namespace Common
{
	class Watch;

	class TimeSmoothedBoolean
	{
	public:
		TimeSmoothedBoolean(const Watch &watch, bool initialValue, double timeTillChange);

		void update(bool value);
		bool get() const;

	private:
		const Watch &m_watch;
		const double m_timeTillChange;
		double m_timeBeforeFirstChange;
		bool m_value;
	};
}
}

#endif


