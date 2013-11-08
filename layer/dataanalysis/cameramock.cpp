#include "layer/dataanalysis/cameramock.h"

using namespace RoboHockey::Layer::DataAnalysis;


CameraMock::CameraMock() :
	m_isGoalYellow(false),
	m_cameraObject(new CameraObject(Common::ColorTypeFalse, cv::Rect(0,0,1,1)))
{ }

CameraObject &CameraMock::getCameraObject() const
{
	return *m_cameraObject;
}

bool CameraMock::isGoalYellow() const
{
	return m_isGoalYellow;
}

void CameraMock::setIsGoalYellow(bool value)
{
	m_isGoalYellow = value;
}
