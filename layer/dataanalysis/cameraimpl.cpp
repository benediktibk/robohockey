#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/camera.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace cv;

CameraImpl::CameraImpl(Hardware::Camera &camera) :
	m_camera(camera)
{ }

void CameraImpl::getColor() const
{ }

Mat CameraImpl::getsmoothFrame()
{
	Mat frame = m_camera.getFrame();
	Mat smoothFrame = frame;

	cvSmooth(&frame, &smoothFrame, CV_MEDIAN, 9 , 9);
	return smoothFrame;
}
