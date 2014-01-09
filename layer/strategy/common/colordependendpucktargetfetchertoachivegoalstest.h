#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERTOACHIVEGOALSTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERTOACHIVEGOALSTEST_H

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
	class ColorDependendPuckTargetFetcherToAchiveGoalsTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ColorDependendPuckTargetFetcherToAchiveGoalsTest);
		CPPUNIT_TEST(getColorOfTargetPucks_ownColorIsYellow_resultIsYellow);
		CPPUNIT_TEST(getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1);
		CPPUNIT_TEST(getNumberOfKnownPucksNotInTarget_threePucksOneInGoal_resultIs2);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getColorOfTargetPucks_ownColorIsYellow_resultIsYellow();
		void getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1();
		void getNumberOfKnownPucksNotInTarget_threePucksOneInGoal_resultIs2();
	};
}
}
}
}

#endif


