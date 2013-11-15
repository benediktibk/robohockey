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

		virtual CameraObjects getAllCameraObjects(const Common::RobotPosition &position);
		virtual bool isGoalYellow();

	private:
		void filterFrameAndConvertToHLS();
		void addObjects(ColorType color);
		const Common::Point getCalculatedPosition() const;

	private:
		Hardware::Camera &m_camera;
		cv::Mat m_fileredFrame;
		CameraObjects m_cameraObjects;
		Common::RobotPosition m_position;
	};
}
}
}

#endif
