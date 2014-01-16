#include "layer/dataanalysis/sonarmock.h"

using namespace RoboHockey::Layer::DataAnalysis;

SonarMock::SonarMock() :
	m_isObstacleDirectInFront(false)
{ }

bool SonarMock::isObstacleDirectInFront(double) const
{
	return m_isObstacleDirectInFront;
}

double SonarMock::getLeftFrontValue() const
{
	return 0;
}

double SonarMock::getRightFrontValue() const
{
	return 0;
}

void SonarMock::setIsObstacleDirectInFront(bool value)
{
	m_isObstacleDirectInFront = value;
}
