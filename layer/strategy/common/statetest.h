#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_STATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class StateTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE(StateTest);
		CPPUNIT_TEST(update_updateAlwaysAndCalledThreeTimes_updateInternalWasCalledThreeTimes);
		CPPUNIT_TEST(update_updateOnlyOnceAndCalledFourTimes_updateInternalWasCalledOnce);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_updateAlwaysAndCalledThreeTimes_updateInternalWasCalledThreeTimes();
		void update_updateOnlyOnceAndCalledFourTimes_updateInternalWasCalledOnce();

	};
}
}
}
}

#endif


