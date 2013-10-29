#ifndef ROBOHOCKEY_THREADING_LOCKTEST_H
#define ROBOHOCKEY_THREADING_LOCKTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Threading
{
	class LockTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(LockTest);
		 CPPUNIT_TEST(constructor_validMutex_mutexIsLocked);
		 CPPUNIT_TEST(destructor_empty_mutexIsNotLocked);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void constructor_validMutex_mutexIsLocked();
		 void destructor_empty_mutexIsNotLocked();
	};
}

#endif
