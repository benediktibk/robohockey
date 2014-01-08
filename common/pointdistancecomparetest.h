#ifndef ROBOHOCKEY_COMMON_POINTDISTANCECOMPARETEST_H
#define ROBOHOCKEY_COMMON_POINTDISTANCECOMPARETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
class PointDistanceCompareTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(PointDistanceCompareTest);
		CPPUNIT_TEST(compare_firstOneCloserThanSecondOneBecauseOfPosition_true);
		CPPUNIT_TEST(compare_seoncdOneCloserThanFirstOneBecauseOfPosition_false);
		CPPUNIT_TEST_SUITE_END();

	private:

		void compare_firstOneCloserThanSecondOneBecauseOfPosition_true();
		void compare_seoncdOneCloserThanFirstOneBecauseOfPosition_false();
	};
}
}

#endif


