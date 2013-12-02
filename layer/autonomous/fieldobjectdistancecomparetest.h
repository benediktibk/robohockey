#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTDISTANCECOMPARETEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTDISTANCECOMPARETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObjectDistanceCompareTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldObjectDistanceCompareTest);
		CPPUNIT_TEST(compare_firstOneCloserThanSecondOneBecauseOfPosition_true);
		CPPUNIT_TEST(compare_seoncdOneCloserThanFirstOneBecauseOfPosition_false);
		CPPUNIT_TEST(compare_firstOneCloserThanSecondOneBecauseOfBigDiameter_true);
		CPPUNIT_TEST(compare_seoncdOneCloserThanFirstOneBecauseOfBigDiameter_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void compare_firstOneCloserThanSecondOneBecauseOfPosition_true();
		void compare_seoncdOneCloserThanFirstOneBecauseOfPosition_false();
		void compare_firstOneCloserThanSecondOneBecauseOfBigDiameter_true();
		void compare_seoncdOneCloserThanFirstOneBecauseOfBigDiameter_false();
	};
}
}
}

#endif


