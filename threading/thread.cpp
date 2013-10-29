#include "threading/thread.h"
#include "threading/signal.h"
#include <boost/thread.hpp>

using namespace Threading;

Thread::Thread() :
	m_constructionFinished(new Signal()),
	m_finished(new Signal()),
	m_thread(new boost::thread(threadFunction, this))
{ }

Thread::~Thread()
{
	waitTillFinished();
	delete m_thread;
	delete m_finished;
	delete m_constructionFinished;
}

void Thread::waitTillFinished() const
{
	m_finished->wait();
}

void Thread::setConstructionFinished()
{
	m_constructionFinished->send();
}

void Thread::threadFunction(Thread *thread)
{
	thread->m_constructionFinished->wait();
	thread->execute();
	thread->m_finished->send();
}
