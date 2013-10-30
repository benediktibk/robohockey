#include "threading/lock.h"
#include "threading/mutex.h"

using namespace RoboHockey::Threading;

Lock::Lock(Mutex &mutex) :
	m_mutex(mutex)
{
	m_mutex.lock();
}

Lock::~Lock()
{
	m_mutex.unlock();
}
