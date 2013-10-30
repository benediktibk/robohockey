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
		CameraImpl(int device=0);
		~CameraImpl();

		virtual cv::Mat getFrame();

	private:
		cv::VideoCapture *m_capture;

	};
}
}
}

#endif
