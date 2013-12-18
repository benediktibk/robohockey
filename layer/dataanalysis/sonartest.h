#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SONARTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SONARTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class SonarTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(SonarTest);
		CPPUNIT_TEST(isObstacleInFront_mockHardwareSonar_atLeastOneCallToGetDistanceForSensor);
		CPPUNIT_TEST(isObstacleInFront_nothingInFront_false);
		CPPUNIT_TEST(isObstacleInFront_obstacleIn03meter_true);
		CPPUNIT_TEST(isObstacleInFront_farDistant_false);
		CPPUNIT_TEST(isObstacleInFront_closeEnough_true);
		CPPUNIT_TEST(isObstacleInFront_bothSensorsCovered_false);
		CPPUNIT_TEST(isObstacleInFront_bothSensorsCoveredSecondVersion_false);
		CPPUNIT_TEST(isObstacleInFront_bothSensorsCoveredThirdVersion_false);
		CPPUNIT_TEST(isObstacleInFront_onlyLeftValueTooClose_false);
		CPPUNIT_TEST(isObstacleInFront_onlyRightValueTooClose_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isObstacleInFront_mockHardwareSonar_atLeastOneCallToGetDistanceForSensor();
		void isObstacleInFront_nothingInFront_false();
		void isObstacleInFront_obstacleIn03meter_true();
		void isObstacleInFront_farDistant_false();
		void isObstacleInFront_closeEnough_true();
		void isObstacleInFront_bothSensorsCovered_false();
		void isObstacleInFront_bothSensorsCoveredSecondVersion_false();
		void isObstacleInFront_bothSensorsCoveredThirdVersion_false();
		void isObstacleInFront_onlyLeftValueTooClose_false();
		void isObstacleInFront_onlyRightValueTooClose_false();
	};
}
}
}

#endif
