#include "threadreadloop.h"
#include "layer/hardware/robotimpl.h"

using namespace RoboHockey::Threading;

ThreadReadLoop::ThreadReadLoop()
{ }

void ThreadReadLoop::execute()
{
	m_read().updateSensorData();
}
