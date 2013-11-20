#include "layer/dataanalysis/sonartest.h"
#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonarmock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void SonarTest::isObstacleInFront_mockHardwareSonar_atLeastOneCallToGetDistanceForSensor()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar, 0.3);

	sonar.isObstacleDirectInFront();

	CPPUNIT_ASSERT(hardwareSonar.getCallsToGetDistanceForSensor() > 0);
}

void SonarTest::isObstacleInFront_nothingInFront_false()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar, 0.3);
	hardwareSonar.setValue(3, 5);
	hardwareSonar.setValue(4, 5);

	CPPUNIT_ASSERT(!sonar.isObstacleDirectInFront());
}

void SonarTest::isObstacleInFront_obstacleIn01meter_true()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar, 0.3);
	hardwareSonar.setValue(3, 0.1);
	hardwareSonar.setValue(4, 0.1);

	CPPUNIT_ASSERT(sonar.isObstacleDirectInFront());
}
