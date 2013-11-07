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

Mat CameraImpl::getSmoothFrame()
{
	Mat frame = m_camera.getFrame();
	Mat smoothFrame = frame;

	medianBlur(frame, smoothFrame, 11);
	return smoothFrame;
}

Mat CameraImpl::getFilteredFrame()
{
	Mat frame = getSmoothFrame();
	Mat filteredFrame = frame;

	cvPyrMeanShiftFiltering(&frame, &filteredFrame, 10, 35, 3);
	return filteredFrame;
}
