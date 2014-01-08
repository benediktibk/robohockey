#ifndef ROBOHOCKEY_COMMON_WATCH_H
#define ROBOHOCKEY_COMMON_WATCH_H

namespace RoboHockey
{
namespace Common
{
	class Watch
	{
	public:
		virtual ~Watch() { }

		virtual double getTime() const = 0;
	};
}
}

#endif
