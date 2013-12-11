#include "layer/dataanalysis/speedtresholdertest.h"
#include "layer/dataanalysis/speedtresholder.h"
#include <math.h>

using namespace RoboHockey::Layer::DataAnalysis;

void SpeedTresholderTest::tresholdWheelSpeeds_0and0_0and0()
{
	SpeedTresholder tresholder;
	double magnitude = 0;
	double rotationSpeed = 0;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, magnitude, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, rotationSpeed, 0.001);
}

void SpeedTresholderTest::tresholdWheelSpeeds_06and0_0507and0()
{
	SpeedTresholder tresholder;
	double magnitude = 0.596902604;
	double rotationSpeed = 0;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.507367213, magnitude, 0.05);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, rotationSpeed, 0.001);
}

void SpeedTresholderTest::tresholdWheelSpeeds_minus06and0_minus0507and0()
{
	SpeedTresholder tresholder;
	double magnitude = -0.596902604;
	double rotationSpeed = 0;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.507367213, magnitude, 0.05);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, rotationSpeed, 0.001);
}

void SpeedTresholderTest::tresholdWheelSpeeds_0and3pi_0and267()
{
	SpeedTresholder tresholder;
	double magnitude = 0;
	double rotationSpeed = 3*M_PI;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, magnitude, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.670353756, rotationSpeed, 0.2);
}

void SpeedTresholderTest::tresholdWheelSpeeds_05andpi_magnitudeToRotationSpeedRatioIsCorrect()
{
	SpeedTresholder tresholder;
	double magnitude = 0.5;
	double rotationSpeed = M_PI;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	double ratio = magnitude/rotationSpeed;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5/M_PI, ratio, 0.001);
}

void SpeedTresholderTest::tresholdWheelSpeeds_07and01_magnitudeToRotationSpeedRatioIsCorrect()
{
	SpeedTresholder tresholder;
	double magnitude = 0.7;
	double rotationSpeed = 0.1;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	double ratio = magnitude/rotationSpeed;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7/0.1, ratio, 0.001);
}

void SpeedTresholderTest::tresholdWheelSpeeds_01and10_magnitudeToRotationSpeedRatioIsCorrect()
{
	SpeedTresholder tresholder;
	double magnitude = 0.1;
	double rotationSpeed = 10;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	double ratio = magnitude/rotationSpeed;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1/10, ratio, 0.001);
}

void SpeedTresholderTest::tresholdWheelSpeeds_01andMinus10_magnitudeToRotationSpeedRatioIsCorrect()
{
	SpeedTresholder tresholder;
	double magnitude = 0.1;
	double rotationSpeed = -10;

	tresholder.tresholdWheelSpeeds(magnitude, rotationSpeed);

	double ratio = magnitude/rotationSpeed;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1/10, ratio, 0.001);
}
