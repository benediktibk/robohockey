#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(Hardware::Sonar &sonar) :
	m_sonar(sonar)
{ }

bool SonarImpl::isObstacleDirectInFront()
{
	double leftFrontValue = m_sonar.getDistanceForSensor(3);
	double rightFrontValue = m_sonar.getDistanceForSensor(4);
	double meanDistance = (leftFrontValue + rightFrontValue)/2;
	double breakingWay = 0.2;
	double lengthOfRobot = 0.1;
	double angst = 0.1;

	if (meanDistance < breakingWay + lengthOfRobot + angst)
		return true;
	else
		return false;
}
