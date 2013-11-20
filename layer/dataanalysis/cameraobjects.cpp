#include "layer/dataanalysis/cameraobjects.h"
#include "common/compare.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;
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

const CameraObject &CameraObjects::front() const
{
	return m_objects.front();
}

const CameraObject &CameraObjects::back() const
{
	return m_objects.back();
}

const CameraObject &CameraObjects::getCameraObjectAtPosition(const Common::Point &position) const
{
	Compare compare(0.05);
	Point nextToPosition(0,0);
	int objectNumberNextToPosition;
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if(compare.isFuzzyEqual(position, m_objects[i].getPosition()))
			return m_objects[i];
		if(nextToPosition.distanceTo(position) > m_objects[i].getPosition().distanceTo(position))
		{
			nextToPosition = m_objects[i].getPosition();
			objectNumberNextToPosition = i;
		}
	}
	return m_objects[objectNumberNextToPosition];
}

const CameraObject &CameraObjects::operator [](size_t index) const
{
	return m_objects[index];
}

void CameraObjects::clear()
{
	m_objects.clear();
}
