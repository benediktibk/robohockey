#ifndef ROBOHOCKEY_THREADING_THREADREADLOOP_H
#define ROBOHOCKEY_THREADING_THREADREADLOOP_H

#include "thread.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class RobotImpl;
}
}
namespace Threading
{
class ThreadReadLoop :
		public Thread
{
public:
	ThreadReadLoop();

	virtual void execute();

private:
	Layer::Hardware::RobotImpl &m_read();
};
}
}

#endif
