#ifndef ROBOHOCKEY_LAYER_STRATEGY_INITIALSTATETEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_INITIALSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
	class InitialStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(InitialStateTest);
        CPPUNIT_TEST(update_empty_stateGotAtLeastOneCallToNextState);
		CPPUNIT_TEST_SUITE_END();

	private:
        void update_empty_stateGotAtLeastOneCallToNextState();
	};
}
}
}

#endif
