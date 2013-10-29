#include "mutextest.h"
#include "threading/mutex.h"
#include "threading/thread.h"
#include <vector>

using namespace Threading;
using namespace std;

class ThreadMutexTestImplementation :
		public Thread
{
public:
	ThreadMutexTestImplementation(Mutex &mutex, double &value) :
		m_mutex(mutex),
		m_value(value)
	{
		setConstructionFinished();
	}

private:
	virtual void execute()
	{
		for (size_t i = 0; i < 1000; ++i)
		{
			m_mutex.lock();
			++m_value;
			m_mutex.unlock();
		}
	}

private:
	Mutex &m_mutex;
	double &m_value;
};

void MutexTest::lock_100ThreadsWhichEachIncreaseDoubleVariable1000Times_variablesIs100000()
{
	vector<Thread*> threads;
	threads.reserve(100);
	double value = 0;
	Mutex mutex;

	for (size_t i = 0; i < 100; ++i)
		threads.push_back(new ThreadMutexTestImplementation(mutex, value));

	for (vector<Thread*>::const_iterator i = threads.begin(); i != threads.end(); ++i)
		(*i)->waitTillFinished();

	for (vector<Thread*>::const_iterator i = threads.begin(); i != threads.end(); ++i)
		delete *i;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(100000, value, 0.000001);
}
