#include "layer/dataanalysis/cameraobjects.h"

using namespace RoboHockey::Layer::DataAnalysis;

CameraObjects::CameraObjects()
{
}

void CameraObjects::addObject(const CameraObject &object)
{
	m_objects.push_back(object);
}

size_t CameraObjects::getObjectCount() const
{
	return m_objects.size();
}
