#ifndef ROBOHOCKEY_THREADING_THREADTEST_H
#define ROBOHOCKEY_THREADING_THREADTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Threading
{
class ThreadTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(ThreadTest);
	 CPPUNIT_TEST(constructor_setValueTo5DuringExecution_valueIs5);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void constructor_setValueTo5DuringExecution_valueIs5();
};
}

#endif
