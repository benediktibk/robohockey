#include "layer/autonomous/borderstonedistancestest.h"
#include "layer/autonomous/borderstonedistances.h"

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::getStandardFieldDistance_A_isCorrectDistance()
{
	BorderStoneDistances distancesChecker(0.07);
	BorderStoneFieldDistance currentDistance = BorderStoneFieldDistanceA;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.25 * 5.0 / 3.0, distancesChecker.getStandardFieldDistance(currentDistance), 0.0001);
}

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::getStandardFieldDistance_B_isCorrectDistance()
{
	BorderStoneDistances distancesChecker(0.07);
	BorderStoneFieldDistance currentDistance = BorderStoneFieldDistanceB;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(15.0 / 12.0, distancesChecker.getStandardFieldDistance(currentDistance), 0.0001);
}

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::getStandardFieldDistance_C_isCorrectDistance()
{
	BorderStoneDistances distancesChecker(0.07);
	BorderStoneFieldDistance currentDistance = BorderStoneFieldDistanceC;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5 * 5.0 / 3.0, distancesChecker.getStandardFieldDistance(currentDistance), 0.0001);
}

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::getStandardFieldDistance_D_isCorrectDistance()
{
	BorderStoneDistances distancesChecker(0.07);
	BorderStoneFieldDistance currentDistance = BorderStoneFieldDistanceD;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, distancesChecker.getStandardFieldDistance(currentDistance), 0.0001);
}

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::distanceIsStandardDistance_nonStandardDistance_false()
{
	BorderStoneDistances distancesChecker(0.07);
	double testValue = 1.79;

	CPPUNIT_ASSERT_EQUAL(distancesChecker.isDistanceStandardDistance(testValue), false);
}

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::distanceIsStandardDistance_StandardDistance_true()
{
	BorderStoneDistances distancesChecker(0.07);
	double testValue = 0.41;

	CPPUNIT_ASSERT_EQUAL(distancesChecker.isDistanceStandardDistance(testValue), true);
}

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::checkForStandardDistance_fuzzyDistanceC_distanceC()
{
	BorderStoneDistances distancesChecker(0.07);
	double testValue = 0.83;

	CPPUNIT_ASSERT_EQUAL(distancesChecker.getStandardDistanceType(testValue), BorderStoneFieldDistanceC);
}

void RoboHockey::Layer::Autonomous::BorderStoneDistancesTest::checkForStandardDistance_nonStandardDistance_falseDistance()
{
	BorderStoneDistances distancesChecker(0.07);
	double testValue = 0.01;

	CPPUNIT_ASSERT_EQUAL(distancesChecker.getStandardDistanceType(testValue), BorderStoneFieldDistanceFalse);
}
