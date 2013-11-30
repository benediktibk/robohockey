#ifndef ROBOHOCKEY_COMMON_PATHTEST_H
#define ROBOHOCKEY_COMMON_PATHTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class PathTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(PathTest);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromLeft_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromRight_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromStart_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromEnd_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIsInThePath_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circlePassesThePath_resultIsFalse);
		 CPPUNIT_TEST(intersectsWith_pathFromRightToLeftAndCircleFarAwayRight_false);
		 CPPUNIT_TEST(isCircleOnPath_circleOnPath_true);
		 CPPUNIT_TEST(isCircleOnPath_circleCenterIsNotOnPath_false);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void intersectsWith_circleIntersectsPathFromLeft_resultIsTrue();
		 void intersectsWith_circleIntersectsPathFromRight_resultIsTrue();
		 void intersectsWith_circleIntersectsPathFromStart_resultIsTrue();
		 void intersectsWith_circleIntersectsPathFromEnd_resultIsTrue();
		 void intersectsWith_circleIsInThePath_resultIsTrue();
		 void intersectsWith_circlePassesThePath_resultIsFalse();
		 void intersectsWith_pathFromRightToLeftAndCircleFarAwayRight_false();
		 void isCircleOnPath_circleOnPath_true();
		 void isCircleOnPath_circleCenterIsNotOnPath_false();

	};
}
}

#endif
