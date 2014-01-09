#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERTOHIDEPUCKSTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_COLORDEPENDENDPUCKTARGETFETCHERTOHIDEPUCKSTEST_H

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
	class ColorDependendPuckTargetFetcherToHidePucksTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ColorDependendPuckTargetFetcherToHidePucksTest);
		CPPUNIT_TEST(getColorOfTargetPucks_ownColorIsYellow_resultIsBlue);
		CPPUNIT_TEST(getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1);
		CPPUNIT_TEST(getNumberOfKnownPucksNotInTarget_threePucksOnePuckHidden_resultIs2);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getColorOfTargetPucks_ownColorIsYellow_resultIsBlue();
		void getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1();
		void getNumberOfKnownPucksNotInTarget_threePucksOnePuckHidden_resultIs2();

	};
}
}
}
}

#endif


