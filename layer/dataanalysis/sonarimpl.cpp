#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(Hardware::Sonar &sonar) :
	m_sonar(sonar)
{ }

bool SonarImpl::isObstacleDirectInFront(double)
{
	const double leftFrontValue = m_sonar.getDistanceForSensor(3);
	const double rightFrontValue = m_sonar.getDistanceForSensor(4);

	if (	leftFrontValue < 0.2 ||
			rightFrontValue < 0.2)
		return true;
	else
		return false;
}
