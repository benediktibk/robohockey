#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_WAITSTATETEST_H

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
	class WaitStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(WaitStateTest);
		CPPUNIT_TEST(nextState_didntWaitEnoughCycles_resultIs0);
		CPPUNIT_TEST(nextState_didWaitEnoughCycles_resultIsStateAfterWaitCycles);
		CPPUNIT_TEST_SUITE_END();

	private:
		void nextState_didntWaitEnoughCycles_resultIs0();
		void nextState_didWaitEnoughCycles_resultIsStateAfterWaitCycles();
	
};
}
}
}
}

#endif


