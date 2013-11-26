#include "layer/dataanalysis/cameramock.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;


CameraMock::CameraMock() :
	m_isGoalYellow(0)
{ }

CameraObjects CameraMock::getAllCameraObjects(const RobotPosition &)
{
	return CameraObjects();
}

double CameraMock::getProbabilityForYellowGoal()
{
	return m_isGoalYellow;
}

void CameraMock::setIsGoalYellow(bool value)
{
	m_isGoalYellow = value;
}

void CameraMock::setAllObjects(const CameraObjects &objects)
{
	m_objects = objects;
}


