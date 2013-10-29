#include "threading/locktest.h"
#include "threading/lock.h"
#include "threading/mutex.h"

using namespace Threading;

void LockTest::constructor_validMutex_mutexIsLocked()
{
	Mutex mutex;
	Lock lock(mutex);

	CPPUNIT_ASSERT(mutex.isLocked());
}

void LockTest::destructor_empty_mutexIsNotLocked()
{
	Mutex mutex;

	{
		Lock lock(mutex);
	}

	CPPUNIT_ASSERT(!mutex.isLocked());
}
