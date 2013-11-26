#include "layer/dataanalysis/sonartest.h"
#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonarmock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void SonarTest::isObstacleInFront_mockHardwareSonar_atLeastOneCallToGetDistanceForSensor()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar);

	sonar.isObstacleDirectInFront(1);

	CPPUNIT_ASSERT(hardwareSonar.getCallsToGetDistanceForSensor() > 0);
}

void SonarTest::isObstacleInFront_nothingInFront_false()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar);
	hardwareSonar.setValue(3, 5);
	hardwareSonar.setValue(4, 5);

	CPPUNIT_ASSERT(!sonar.isObstacleDirectInFront(1));
}

void SonarTest::isObstacleInFront_obstacleIn01meter_true()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar);
	hardwareSonar.setValue(3, 0.1);
	hardwareSonar.setValue(4, 0.1);

	CPPUNIT_ASSERT(sonar.isObstacleDirectInFront(1));
}

void SonarTest::isObstacleInFront_farDistant_false()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar);
	hardwareSonar.readSensorDataFromFile("resources/testfiles/sonar_1.txt");

	CPPUNIT_ASSERT(!sonar.isObstacleDirectInFront(0.5));
}
