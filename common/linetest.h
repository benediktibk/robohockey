#ifndef ROBOHOCKEY_COMMON_LINETEST_H
#define ROBOHOCKEY_COMMON_LINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class LineTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(LineTest);
		 CPPUNIT_TEST(getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0);
		 CPPUNIT_TEST(getIntersectPoints_circleToutchesLine_intersectPointsCountIs1);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0();
		 void getIntersectPoints_circleToutchesLine_intersectPointsCountIs1();
		 void getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2();
	};
}
}

#endif
