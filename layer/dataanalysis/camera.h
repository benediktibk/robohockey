#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H

#include "layer/dataanalysis/cameraobject.h"

namespace cv
{
class Mat;
}

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class Camera
	{
	public:
		virtual ~Camera() { }

		virtual CameraObject& getCameraObject() const = 0;
		virtual bool isGoalYellow() const = 0;
	};
}
}
}

#endif
