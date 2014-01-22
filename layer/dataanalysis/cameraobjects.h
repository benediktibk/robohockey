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
		const CameraObject& front() const;
		const CameraObject& back() const;
		const CameraObject& getCameraObjectAtPosition(const Common::Point &position) const;
		const std::vector<CameraObject>& getAllObjects() const;

		const CameraObject& operator[](size_t index) const;
		void clear();

	private:
		std::vector<CameraObject> m_objects;
	};
}
}
}
#endif
