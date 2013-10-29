#include "threadtest.h"
#include "threading/thread.h"

using namespace Threading;

class ThreadTestImplementation :
		public Thread
{
public:
	ThreadTestImplementation() :
		m_value(0)
	{
		setConstructionFinished();
	}

	int getValue() const
	{
		return m_value;
	}

private:
	virtual void execute()
	{
		m_value = 5;
	}

private:
	int m_value;
};

void ThreadTest::constructor_setValueTo5DuringExecution_valueIs5()
{
	ThreadTestImplementation thread;

	thread.waitTillFinished();

	CPPUNIT_ASSERT_EQUAL((int)5, thread.getValue());
}
