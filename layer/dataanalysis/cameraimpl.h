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
		virtual double getProbabilityForYellowGoal();
		virtual double getProbabilityForBlueGoal();

	private:
		void filterFrameAndConvertToHLS();
		void addObjects(Common::FieldObjectColor color);
		const Common::Point getCalculatedPosition(cv::Point pixel, double distanceToCenter) const;

	private:
		Hardware::Camera &m_camera;
		cv::Mat m_filteredFrame;
		CameraObjects m_cameraObjects;
		Common::RobotPosition m_ownPosition;
	};
}
}
}

#endif
