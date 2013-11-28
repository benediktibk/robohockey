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
		 CPPUNIT_TEST(getIntersectPoints_circleToutchesLineAt0And2_intersectPointsIs0And2);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineAtMinus1And1_intersectPointsIsMinus1And1);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineAt1And1_intersectPointsIs1And1);
		 CPPUNIT_TEST(getIntersectPoints_circleAt1And1IntersectsLineAt2And2_intersectPointsIs2And2);
		 CPPUNIT_TEST(getIntersectPoints_lineIsVertical_intersectPointIsMinus1AndMinus1);
		 CPPUNIT_TEST(getIntersectPoints_lineIsVerticalAndCircleIsNotAt0And0_intersectPointIs2And2);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0();
		 void getIntersectPoints_circleToutchesLine_intersectPointsCountIs1();
		 void getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2();
		 void getIntersectPoints_circleToutchesLineAt0And2_intersectPointsIs0And2();
		 void getIntersectPoints_circleIntersectsLineAtMinus1And1_intersectPointsIsMinus1And1();
		 void getIntersectPoints_circleIntersectsLineAt1And1_intersectPointsIs1And1();
		 void getIntersectPoints_circleAt1And1IntersectsLineAt2And2_intersectPointsIs2And2();
		 void getIntersectPoints_lineIsVertical_intersectPointIsMinus1AndMinus1();
		 void getIntersectPoints_lineIsVerticalAndCircleIsNotAt0And0_intersectPointIs2And2();
	};
}
}

#endif
