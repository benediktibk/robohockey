#ifndef ROBOHOCKEY_THREADING_MUTEXTEST_H
#define ROBOHOCKEY_THREADING_MUTEXTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Threading
{
class MutexTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(MutexTest);
	 CPPUNIT_TEST(lock_100ThreadsWhichEachIncreaseDoubleVariable1000Times_variablesIs100000);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void lock_100ThreadsWhichEachIncreaseDoubleVariable1000Times_variablesIs100000();
};
}
}

#endif
