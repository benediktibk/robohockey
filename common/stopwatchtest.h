#ifndef ROBOHOCKEY_COMMON_STOPWATCHTEST_H
#define ROBOHOCKEY_COMMON_STOPWATCHTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class StopWatchTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(StopWatchTest);
		CPPUNIT_TEST(getTimeAndRestart_twiceDirectBehindCalled_0);
		CPPUNIT_TEST(getTimeAndRestart_sleepOf200ms_02);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getTimeAndRestart_twiceDirectBehindCalled_0();
		void getTimeAndRestart_sleepOf200ms_02();
	};
}
}

#endif


