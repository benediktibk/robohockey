#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTS_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTS_H

#include "layer/dataanalysis/cameraobject.h"
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
		std::vector<CameraObject> getAllCameraObjects();

		const CameraObject& operator[](size_t index) const;

	private:
		std::vector<CameraObject> m_objects;
	};
}
}
}
#endif
