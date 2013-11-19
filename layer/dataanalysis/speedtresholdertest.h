#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SPEEDTRESHOLDERTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SPEEDTRESHOLDERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class SpeedTresholderTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(SpeedTresholderTest);
		CPPUNIT_TEST(tresholdWheelSpeeds_0and0_0and0);
		CPPUNIT_TEST(tresholdWheelSpeeds_06and0_0507and0);
		CPPUNIT_TEST(tresholdWheelSpeeds_minus06and0_minus0507and0);
		CPPUNIT_TEST(tresholdWheelSpeeds_0and3pi_0and267);
		CPPUNIT_TEST(tresholdWheelSpeeds_05andpi_magnitudeToRotationSpeedRatioIsCorrect);
		CPPUNIT_TEST(tresholdWheelSpeeds_07and01_magnitudeToRotationSpeedRatioIsCorrect);
		CPPUNIT_TEST(tresholdWheelSpeeds_01and10_magnitudeToRotationSpeedRatioIsCorrect);
		CPPUNIT_TEST(tresholdWheelSpeeds_01andMinus10_magnitudeToRotationSpeedRatioIsCorrect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void tresholdWheelSpeeds_0and0_0and0();
		void tresholdWheelSpeeds_06and0_0507and0();
		void tresholdWheelSpeeds_minus06and0_minus0507and0();
		void tresholdWheelSpeeds_0and3pi_0and267();
		void tresholdWheelSpeeds_05andpi_magnitudeToRotationSpeedRatioIsCorrect();
		void tresholdWheelSpeeds_07and01_magnitudeToRotationSpeedRatioIsCorrect();
		void tresholdWheelSpeeds_01and10_magnitudeToRotationSpeedRatioIsCorrect();
		void tresholdWheelSpeeds_01andMinus10_magnitudeToRotationSpeedRatioIsCorrect();
	};
}
}
}

#endif
