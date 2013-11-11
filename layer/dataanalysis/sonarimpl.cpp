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
    int counter = 0;
    double distance = 0;
    bool isDirectInFront = false;
    for(int i = 2; i < 6; i++)
    {
        if(m_sonar.getDistanceForSensor(i)<0.3)
            counter += 1;
        sum += m_sonar.getDistanceForSensor(i);       
    }
    sum += m_sonar.getDistanceForSensor(3);
    sum += m_sonar.getDistanceForSensor(4);
    distance = sum/6;
    if (distance < 0.5)
        isDirectInFront = true;
    else if(counter>=3)
        isDirectInFront = true;
    return isDirectInFront;
}
