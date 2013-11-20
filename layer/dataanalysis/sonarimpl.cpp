#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(Hardware::Sonar &sonar, double minimumDistanceToObstacle) :
	m_sonar(sonar),
	m_distanceOfSensorsToMiddleOfRobot(0.15),
	m_minimumDistanceToObstacle(minimumDistanceToObstacle - m_distanceOfSensorsToMiddleOfRobot),
	m_minimumDistanceWithAngst(m_minimumDistanceToObstacle + 0.1)
{ }

bool SonarImpl::isObstacleDirectInFront()
{
	double leftFrontValue = m_sonar.getDistanceForSensor(3);
	double rightFrontValue = m_sonar.getDistanceForSensor(4);

	if (	leftFrontValue < m_minimumDistanceWithAngst ||
			rightFrontValue < m_minimumDistanceWithAngst)
		return true;
	else
		return false;
}
