#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTIONRESULTTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTIONRESULTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
class FieldDetectionResultTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldDetectionResultTest);
		CPPUNIT_TEST(getTransformationDestination_initWithPoint_pointIs0And0);
		CPPUNIT_TEST(getTransformationDestination_initWithPoint_pointIs1And2);
		CPPUNIT_TEST(isEqualDetectionResult_pointFarAway_FALSE);
		CPPUNIT_TEST(isEqualDetectionResult_pointNearButWrongOrientation_FALSE);
		CPPUNIT_TEST(isEqualDetectionResult_pointFarButEqualOrientation_FALSE);
		CPPUNIT_TEST(isEqualDetectionResult_pointFuzzyEqual_TRUE);
		CPPUNIT_TEST(isEqualDetectionResult_pointGoodOrientationCritical_TRUE);
		CPPUNIT_TEST(confirmDetectionResultWithPosition_pointNotGood_noChangesInCounters);
		CPPUNIT_TEST(confirmDetectionResultWithPosition_pointGoodAndOnSameSide_notConfirmedButCounterIncreased);
		CPPUNIT_TEST(confirmDetectionResultWithPosition_pointGoodAndOnOtherSide_confirmedAndCounterIncreased);
		CPPUNIT_TEST_SUITE_END();
	private:
		
		void getTransformationDestination_initWithPoint_pointIs0And0();
		void getTransformationDestination_initWithPoint_pointIs1And2();
		void isEqualDetectionResult_pointFarAway_FALSE();
		void isEqualDetectionResult_pointNearButWrongOrientation_FALSE();
		void isEqualDetectionResult_pointFarButEqualOrientation_FALSE();
		void isEqualDetectionResult_pointFuzzyEqual_TRUE();
		void isEqualDetectionResult_pointGoodOrientationCritical_TRUE();
		void confirmDetectionResultWithPosition_pointNotGood_noChangesInCounters();
		void confirmDetectionResultWithPosition_pointGoodAndOnSameSide_notConfirmedButCounterIncreased();
		void confirmDetectionResultWithPosition_pointGoodAndOnOtherSide_confirmedAndCounterIncreased();

	};
}
}
}

#endif


