#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(Hardware::Sonar &sonar) :
	m_sonar(sonar)
{ }

bool SonarImpl::isObstacleDirectInFront(double speed)
{
	const double leftFrontValue = m_sonar.getDistanceForSensor(3);
	const double rightFrontValue = m_sonar.getDistanceForSensor(4);
	const double distanceOfSensorsToMiddleOfRobot = 0.15;
	const double minimumDistanceToObstacle = 0.4 - distanceOfSensorsToMiddleOfRobot;
	const double timeToStop = 0.2;
	const double brakingDistance = speed*timeToStop;
	const double totalDistance = brakingDistance + minimumDistanceToObstacle;

	if (	leftFrontValue < totalDistance ||
			rightFrontValue < totalDistance)
		return true;
	else
		return false;
}
