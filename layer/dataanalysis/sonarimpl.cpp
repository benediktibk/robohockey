#include "layer/dataanalysis/sonarimpl.h"
#include "layer/hardware/sonar.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

SonarImpl::SonarImpl(Hardware::Sonar &sonar) :
	m_sonar(sonar)
{ }

bool SonarImpl::isObstacleDirectInFront()
{
    double sum = 0;
    for(int i = 2; i < 6; i++)
        sum += m_sonar.getDistanceForSensor(i);
    sum = sum/4;
    return false;
}
