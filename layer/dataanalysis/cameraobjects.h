#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTS_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTS_H

#include "layer/dataanalysis/cameraobject.h"
#include <list>
#include <vector>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraObjects
	{
	public:
		CameraObjects();

		void addObject(const CameraObject &object);
		size_t getObjectCount() const;

	private:
		std::list<CameraObject> m_objects;
	};
}
}
}
#endif
