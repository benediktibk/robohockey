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
    double distance = 0;
    bool isDirectInFront = false;
    for(int i = 2; i < 6; i++)
        sum += m_sonar.getDistanceForSensor(i);
    distance = sum/4;
    if (distance < 0.2)
        isDirectInFront = true;
    return isDirectInFront;
}
