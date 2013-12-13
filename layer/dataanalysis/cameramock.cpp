#include "layer/dataanalysis/cameramock.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;


CameraMock::CameraMock() :
	m_probabilityForYellow(0),
	m_probabilityForBlue(0),
	m_probabilityForYellowPuck(0),
	m_probabilityForBluePuck(0)
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

double CameraMock::getProbabilityForCollectedYellowPuck()
{
	return m_probabilityForYellowPuck;
}

double CameraMock::getProbabilityForCollectedBluePuck()
{
	return m_probabilityForBluePuck;
}

void CameraMock::setProbabilityForYellowGoal(double value)
{
	m_probabilityForYellow = value;
}

void CameraMock::setProbabilityForBlueGoal(double value)
{
	m_probabilityForBlue = value;
}

void CameraMock::setProbabilityForCollectedYellowPuck(double value)
{
	m_probabilityForYellowPuck = value;
}

void CameraMock::setProbabilityForCollectedBluePuck(double value)
{
	m_probabilityForBluePuck = value;
}

void CameraMock::setAllObjects(const CameraObjects &objects)
{
	m_objects = objects;
}


