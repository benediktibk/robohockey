#include "layer/dataanalysis/cameraobjects.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

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

list<CameraObject> CameraObjects::getAllCameraObjects()
{
	return m_objects;
}
