#include "layer/dataanalysis/cameramock.h"

using namespace RoboHockey::Layer::DataAnalysis;


CameraMock::CameraMock() :
	m_isGoalYellow(false)
{ }

CameraObjects CameraMock::getAllCameraObjects()
{
	CameraObjects objects;
	objects.addObject(CameraObject(ColorTypeFalse,cv::Rect(0,0,1,1)));
	return objects;
}

bool CameraMock::isGoalYellow()
{
	return m_isGoalYellow;
}

void CameraMock::setIsGoalYellow(bool value)
{
	m_isGoalYellow = value;
}
