#include "common/pidcontrollertest.h"
#include "common/pidcontroller.h"
#include "common/watchmock.h"

using namespace RoboHockey::Common;

void PIDControllerTest::setUp()
{
	m_watch = new WatchMock();
}

void PIDControllerTest::tearDown()
{
	delete m_watch;
	m_watch = 0;
}

void PIDControllerTest::evaluate_onlyProportional_correctResult()
{
	PIDController controller(2, 0, 0, *m_watch);

	double result = controller.evaluate(3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, result, 0.00001);
}

void PIDControllerTest::evaluate_onlyProportionalAndTwiceCalled_correctResult()
{
	PIDController controller(0.1, 0, 0, *m_watch);

	controller.evaluate(3);
	double result = controller.evaluate(0.3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.03, result, 0.00001);
}

void PIDControllerTest::evaluate_onlyIntegral_correctResult()
{
	PIDController controller(0, 0.1, 0, *m_watch);

	m_watch->setTime(0.1);
	double result = controller.evaluate(2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.02, result, 0.00001);
}

void PIDControllerTest::evaluate_onlyIntegralAndTwiceCalled_correctResult()
{
	PIDController controller(0, 0.1, 0, *m_watch);

	m_watch->setTime(1);
	controller.evaluate(1);
	m_watch->setTime(2);
	double result = controller.evaluate(3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4, result, 0.00001);
}

void PIDControllerTest::evaluate_onlyIntegralAndThriceCalled_correctResult()
{
	PIDController controller(0, 0.2, 0, *m_watch);

	m_watch->setTime(1);
	controller.evaluate(1);
	m_watch->setTime(2);
	controller.evaluate(0.1);
	m_watch->setTime(3);
	double result = controller.evaluate(1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.42, result, 0.00001);
}

void PIDControllerTest::evaluate_onlyDifferential_correctResult()
{
	PIDController controller(0, 0, 2, *m_watch);

	m_watch->setTime(0.2);
	double result = controller.evaluate(0.1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, result, 0.00001);
}

void PIDControllerTest::evaluate_onlyDifferentialAndNoTimePassed_correctResult()
{
	PIDController controller(0, 0, 2, *m_watch);

	m_watch->setTime(0);
	double result = controller.evaluate(0.1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(20, result, 0.00001);
}

void PIDControllerTest::evaluate_onlyDifferentialAndTwiceCalled_correctResult()
{
	PIDController controller(0, 0, 2, *m_watch);

	m_watch->setTime(1);
	controller.evaluate(2);
	m_watch->setTime(5);
	double result = controller.evaluate(3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, result, 0.00001);
}

void PIDControllerTest::evaluate_allPartsEnabled_correctResult()
{
	PIDController controller(10, 2, 0.5, *m_watch);

	m_watch->setTime(0.1);
	controller.evaluate(2);
	m_watch->setTime(0.15);
	double result = controller.evaluate(0.2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-15.58, result, 0.00001);
}

void PIDControllerTest::resetTo_onlyIntegralAndEvaluatedAfterwards_correctResult()
{
	PIDController controller(0, 1, 0, *m_watch);

	m_watch->setTime(0.1);
	controller.resetTo(1);
	m_watch->setTime(2.1);
	double result = controller.evaluate(3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, result, 0.00001);
}

void PIDControllerTest::resetTo_onlyDifferentialAndEvaluatedAfterwards_correctResult()
{
	PIDController controller(0, 0, 1, *m_watch);

	m_watch->setTime(1);
	controller.resetTo(2);
	m_watch->setTime(1.2);
	double result = controller.evaluate(3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, result, 0.00001);
}
