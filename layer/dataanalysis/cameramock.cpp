#include "layer/dataanalysis/cameramock.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;


CameraMock::CameraMock() :
	m_isGoalYellow(false)
{ }

CameraObjects CameraMock::getAllCameraObjects(const RobotPosition &)
{
	return CameraObjects();
}

bool CameraMock::isGoalYellow()
{
	return m_isGoalYellow;
}

void CameraMock::setIsGoalYellow(bool value)
{
	m_isGoalYellow = value;
}
