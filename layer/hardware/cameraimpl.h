#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H

#include "layer/hardware/camera.h"
#include <opencv2/opencv.hpp>

namespace PlayerCc
{
	class PlayerClient;
}
namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class CameraImpl :
			public Camera
	{
	public:
		CameraImpl();

		virtual cv::Mat getFrame();

	};
}
}
}

#endif
