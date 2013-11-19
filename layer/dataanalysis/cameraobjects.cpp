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

std::vector<CameraObject> CameraObjects::getAllCameraObjects()
{
	return m_objects;
}

const CameraObject &CameraObjects::operator [](size_t index) const
{
	return m_objects[index];
}
