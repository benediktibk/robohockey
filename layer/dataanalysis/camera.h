#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H

#include "layer/dataanalysis/cameraobjects.h"
#include "common/robotposition.h"

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

		virtual CameraObjects getAllCameraObjects(const Common::RobotPosition &position) = 0;
		virtual double getProbabilityForYellowGoal() = 0;
		virtual double getProbabilityForBlueGoal() = 0;
	};
}
}
}

#endif
