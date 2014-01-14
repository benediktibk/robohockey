#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITCYCLESSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITCYCLESSTATETEST_H

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
	class WaitCyclesStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(WaitCyclesStateTest);
		CPPUNIT_TEST(nextState_didntWaitEnoughCycles_resultIs0);
		CPPUNIT_TEST(nextState_didWaitEnoughCycles_resultIsStateAfterWaitCycles);
		CPPUNIT_TEST(nextState_detectAllObjects_resultIsIsStateAfterWaitCycles);
		CPPUNIT_TEST(nextState_shouldWaitTheWholeTime_resultIsIsStateAfterWaitCycles);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_didntWaitEnoughCycles_resultIs0();
		void nextState_didWaitEnoughCycles_resultIsStateAfterWaitCycles();
		void nextState_detectAllObjects_resultIsIsStateAfterWaitCycles();
		void nextState_shouldWaitTheWholeTime_resultIsIsStateAfterWaitCycles();
	
};
}
}
}
}

#endif


