#include "common/timesmoothedboolean.h"
#include "common/watch.h"

using namespace RoboHockey::Common;

TimeSmoothedBoolean::TimeSmoothedBoolean(const Watch &watch, bool initialValue, double timeTillChange) :
	m_watch(watch),
	m_timeTillChange(timeTillChange),
	m_timeBeforeFirstChange(watch.getTime()),
	m_value(initialValue)
{ }

void TimeSmoothedBoolean::update(bool value)
{
	if (value == m_value)
		m_timeBeforeFirstChange = m_watch.getTime();
	else
	{
		double timeDifference = m_watch.getTime() - m_timeBeforeFirstChange;

		if (timeDifference > m_timeTillChange)
		{
			m_value = value;
			m_timeBeforeFirstChange = m_watch.getTime();
		}
	}
}

bool TimeSmoothedBoolean::get() const
{
	return m_value;
}
