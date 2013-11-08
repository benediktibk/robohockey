#include "layer/dataanalysis/cameramock.h"

using namespace RoboHockey::Layer::DataAnalysis;


CameraMock::CameraMock() :
	m_isGoalYellow(false)
{ }

void CameraMock::getColor() const
{ }

bool CameraMock::isGoalYellow() const
{
	return m_isGoalYellow;
}


void CameraMock::setIsGoalYellow(bool value)
{
	m_isGoalYellow = value;
}
