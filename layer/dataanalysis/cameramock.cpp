#include "layer/dataanalysis/cameramock.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;


CameraMock::CameraMock() :
	m_probabilityForYellow(0),
	m_probabilityForBlue(0)
{ }

CameraObjects CameraMock::getAllCameraObjects(const RobotPosition &)
{
	return m_objects;
}

double CameraMock::getProbabilityForYellowGoal()
{
	return m_probabilityForYellow;
}

double CameraMock::getProbabilityForBlueGoal()
{
	return m_probabilityForBlue;
}

void CameraMock::setProbabilityForYellowGoal(bool value)
{
	m_probabilityForYellow = value;
}

void CameraMock::setProbabilityForBlueGoal(bool value)
{
	m_probabilityForBlue = value;
}

void CameraMock::setAllObjects(const CameraObjects &objects)
{
	m_objects = objects;
}


