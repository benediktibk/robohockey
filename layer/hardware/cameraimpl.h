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
		CameraImpl(int device);
		~CameraImpl();

		virtual cv::Mat getFrame() const;
		virtual bool isValid() const;
		virtual void writeDataToFile(const std::string &fileName) const;

	private:
		// forbid copies
		CameraImpl(const CameraImpl &camera);
		void operator=(const CameraImpl &camera);

	private:
		cv::VideoCapture *m_capture;

	};
}
}
}

#endif
