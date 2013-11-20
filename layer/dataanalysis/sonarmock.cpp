#include "layer/dataanalysis/sonarmock.h"

using namespace RoboHockey::Layer::DataAnalysis;

SonarMock::SonarMock() :
	m_isObstacleDirectInFront(false)
{ }

bool SonarMock::isObstacleDirectInFront(double)
{
	return m_isObstacleDirectInFront;
}

void SonarMock::setIsObstacleDirectInFront(bool value)
{
	m_isObstacleDirectInFront = value;
}
