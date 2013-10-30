#include "layer/dataanalysis/sonarimpl.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(const Hardware::Sonar &sonar) :
	m_sonar(sonar)
{ }

bool SonarImpl::isObstacleDirectInFront() const
{
	return false;
}
