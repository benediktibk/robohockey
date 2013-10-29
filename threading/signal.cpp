#include "threading/signal.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <assert.h>

using namespace Threading;
using namespace boost;

Signal::Signal() :
	m_condition(new condition_variable),
	m_conditionMutex(new mutex),
	m_sendingMutex(new mutex),
	m_sent(false)
{ }

Signal::~Signal()
{
	m_conditionMutex->lock();
	m_conditionMutex->unlock();
	m_sendingMutex->lock();
	m_sendingMutex->unlock();

	delete m_condition;
	delete m_conditionMutex;
	delete m_sendingMutex;
}

void Signal::send()
{
	unique_lock<mutex> sendingLock(*m_sendingMutex);

	m_conditionMutex->lock();
	m_sent = true;
	m_condition->notify_all();
	m_conditionMutex->unlock();
}

void Signal::reset()
{
	m_conditionMutex->lock();
	m_sent = false;
	m_conditionMutex->unlock();
}

void Signal::wait()
{
	unique_lock<mutex> lock(*m_conditionMutex);
	while (!m_sent)
		m_condition->wait(lock);
}

bool Signal::isSignalSent() const
{
	unique_lock<mutex> lock(*m_conditionMutex);
	return m_sent;
}
