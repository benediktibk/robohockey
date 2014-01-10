#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHERTOACHIVEGOALSTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENTPUCKTARGETFETCHERTOACHIVEGOALSTEST_H

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
	class ColorDependentPuckTargetFetcherToAchiveGoalsTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ColorDependentPuckTargetFetcherToAchiveGoalsTest);
		CPPUNIT_TEST(getColorOfTargetPucks_ownColorIsYellow_resultIsYellow);
		CPPUNIT_TEST(getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1);
		CPPUNIT_TEST(getNumberOfKnownPucksNotInTarget_threePucksOneInGoal_resultIs2);
		CPPUNIT_TEST(getNumberOfKnownPucksNotInEnemyThird_threePucksOneInGoal_resultIs2);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getColorOfTargetPucks_ownColorIsYellow_resultIsYellow();
		void getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1();
		void getNumberOfKnownPucksNotInTarget_threePucksOneInGoal_resultIs2();
		void getNumberOfKnownPucksNotInEnemyThird_threePucksOneInGoal_resultIs2();
	};
}
}
}
}

#endif


