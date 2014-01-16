#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(Hardware::Sonar &sonar) :
	m_sonar(sonar)
{ }

bool SonarImpl::isObstacleDirectInFront(double speed) const
{
	const double leftFrontValue = getLeftFrontValue();
	const double rightFrontValue = getRightFrontValue();
	const double distanceOfSensorsToMiddleOfRobot = 0.15;
	const double minimumDistanceToObstacle = 0.8 - distanceOfSensorsToMiddleOfRobot;
	const double timeToStop = 0.2;
	const double brakingDistance = speed*timeToStop;
	const double totalDistance = brakingDistance + minimumDistanceToObstacle;
	const double crapBorderForSonar = 0.2;

	if (leftFrontValue < crapBorderForSonar || rightFrontValue < crapBorderForSonar)
		return false;
	else
		return	leftFrontValue < totalDistance && rightFrontValue < totalDistance;
}

double SonarImpl::getLeftFrontValue() const
{
	return m_sonar.getDistanceForSensor(4);
}

double SonarImpl::getRightFrontValue() const
{
	return m_sonar.getDistanceForSensor(3);
}
