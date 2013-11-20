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
		CPPUNIT_TEST(isObstacleInFront_obstacleIn01meter_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isObstacleInFront_mockHardwareSonar_atLeastOneCallToGetDistanceForSensor();
		void isObstacleInFront_nothingInFront_false();
		void isObstacleInFront_obstacleIn01meter_true();
	};
}
}
}

#endif
