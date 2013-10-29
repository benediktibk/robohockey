#include "layer/dataanalysis/sonartest.h"
#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonarmock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void SonarTest::isObstacleInFront_mockHardwareSonar_atLeastOneCallToGetDistanceForSensor()
{
	Hardware::SonarMock hardwareSonar;
	SonarImpl sonar(hardwareSonar);

	sonar.isObstacleDirectInFront();

	CPPUNIT_ASSERT(hardwareSonar.getCallsToGetDistanceForSensor() > 0);
}
