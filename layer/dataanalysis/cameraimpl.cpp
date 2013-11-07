#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/camera.h"
#include <opencv/cv.h>

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace cv;

CameraImpl::CameraImpl(Hardware::Camera &camera) :
	m_camera(camera)
{ }

void CameraImpl::getColor() const
{ }

bool CameraImpl::isGoalYellow() const
{
	//inRange(img, cv::Scalar(105, 185, 200), cv::Scalar(130, 215, 240), img);
	return false;
}

void CameraImpl::filterFrame()
{
	medianBlur(m_camera.getFrame(), m_fileredFrame, 9);
}
