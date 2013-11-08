#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H

#include "layer/dataanalysis/cameraobjects.h"

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

		virtual CameraObjects getAllCameraObjects() const = 0;
		virtual bool isGoalYellow() const = 0;
	};
}
}
}

#endif
