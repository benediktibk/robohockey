#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(Hardware::Sonar &sonar, double minimumDistanceToObstacle, double timeToStop) :
	m_sonar(sonar),
	m_distanceOfSensorsToMiddleOfRobot(0.15),
	m_minimumDistanceToObstacle(minimumDistanceToObstacle - m_distanceOfSensorsToMiddleOfRobot),
	m_minimumDistanceWithAngst(m_minimumDistanceToObstacle + 0.05),
	m_timeToStop(timeToStop)
{ }

bool SonarImpl::isObstacleDirectInFront(double speed)
{
	double leftFrontValue = m_sonar.getDistanceForSensor(3);
	double rightFrontValue = m_sonar.getDistanceForSensor(4);
	double brakingDistance = speed*m_timeToStop;
	double totalDistance = brakingDistance + m_minimumDistanceWithAngst;

	if (	leftFrontValue < totalDistance ||
			rightFrontValue < totalDistance)
		return true;
	else
		return false;
}
