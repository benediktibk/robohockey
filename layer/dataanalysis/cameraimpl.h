#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAIMPL_H

#include "layer/dataanalysis/camera.h"
#include <opencv2/opencv.hpp>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Camera;
}

namespace DataAnalysis
{
	class CameraImpl :
			public Camera
	{
	public:
		CameraImpl(Hardware::Camera &camera);
		virtual void getColor() const;

	private:
		cv::Mat getSmoothFrame();
		cv::Mat getFilteredFrame();


	private:
		Hardware::Camera &m_camera;
	};
}
}
}

#endif
