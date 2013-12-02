#ifndef ROBOHOCKEY_COMMON_PATHINTERSECTPOINTSTEST_H
#define ROBOHOCKEY_COMMON_PATHINTERSECTPOINTSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
class PathIntersectPointsTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(PathIntersectPointsTest);
	CPPUNIT_TEST(constructor_createDefaultObject_intersectPointsCountIs2);
	CPPUNIT_TEST(constructor_createDefaultObject_intersectTypeFromLeft);
	CPPUNIT_TEST_SUITE_END();

private:
	void constructor_createDefaultObject_intersectPointsCountIs2();
	void constructor_createDefaultObject_intersectTypeFromLeft();
	
};
}
}

#endif // ROBOHOCKEY_COMMON_PATHINTERSECTPOINTSTEST_H


