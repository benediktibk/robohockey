#ifndef ROBOHOCKEY_COMMON_TIMESMOOTHEDBOOLEANTEST_H
#define ROBOHOCKEY_COMMON_TIMESMOOTHEDBOOLEANTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class TimeSmoothedBooleanTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(TimeSmoothedBooleanTest);
		CPPUNIT_TEST(constructor_initialValueTrue_valueIsTrue);
		CPPUNIT_TEST(constructor_initialValueFalse_valueIsFalse);
		CPPUNIT_TEST(update_trueAndThenFalseNearlyLongEnough_true);
		CPPUNIT_TEST(update_falseAndThenTrueNearlyLongEnough_false);
		CPPUNIT_TEST(update_trueAndThenFalseLongEnough_false);
		CPPUNIT_TEST(update_falseAndThenTrueLongEnough_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_initialValueTrue_valueIsTrue();
		void constructor_initialValueFalse_valueIsFalse();
		void update_trueAndThenFalseNearlyLongEnough_true();
		void update_falseAndThenTrueNearlyLongEnough_false();
		void update_trueAndThenFalseLongEnough_false();
		void update_falseAndThenTrueLongEnough_true();
	};
}
}

#endif


