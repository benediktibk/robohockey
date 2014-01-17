#ifndef ROBOHOCKEY_COMMON_PIDCONTROLLERTEST_H
#define ROBOHOCKEY_COMMON_PIDCONTROLLERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class WatchMock;

	class PIDControllerTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(PIDControllerTest);
		CPPUNIT_TEST(evaluate_onlyProportional_correctResult);
		CPPUNIT_TEST(evaluate_onlyProportionalAndTwiceCalled_correctResult);
		CPPUNIT_TEST(evaluate_onlyIntegral_correctResult);
		CPPUNIT_TEST(evaluate_onlyIntegralAndTwiceCalled_correctResult);
		CPPUNIT_TEST(evaluate_onlyIntegralAndThriceCalled_correctResult);
		CPPUNIT_TEST(evaluate_onlyDifferential_correctResult);
		CPPUNIT_TEST(evaluate_onlyDifferentialAndNoTimePassed_correctResult);
		CPPUNIT_TEST(evaluate_onlyDifferentialAndTwiceCalled_correctResult);
		CPPUNIT_TEST(evaluate_allPartsEnabled_correctResult);
		CPPUNIT_TEST(resetTo_onlyIntegralAndEvaluatedAfterwards_correctResult);
		CPPUNIT_TEST(resetTo_onlyDifferentialAndEvaluatedAfterwards_correctResult);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

	private:
		void evaluate_onlyProportional_correctResult();
		void evaluate_onlyProportionalAndTwiceCalled_correctResult();
		void evaluate_onlyIntegral_correctResult();
		void evaluate_onlyIntegralAndTwiceCalled_correctResult();
		void evaluate_onlyIntegralAndThriceCalled_correctResult();
		void evaluate_onlyDifferential_correctResult();
		void evaluate_onlyDifferentialAndNoTimePassed_correctResult();
		void evaluate_onlyDifferentialAndTwiceCalled_correctResult();
		void evaluate_allPartsEnabled_correctResult();
		void resetTo_onlyIntegralAndEvaluatedAfterwards_correctResult();
		void resetTo_onlyDifferentialAndEvaluatedAfterwards_correctResult();

	private:
		WatchMock *m_watch;
	};
}
}

#endif


