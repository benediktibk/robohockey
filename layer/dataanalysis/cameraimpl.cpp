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

Mat CameraImpl::getFilteredFrame(unsigned int threshold)
{
	Mat frame = getSmoothFrame();
	Mat filteredFrame = frame;

	//threshold used for building but will be used for parameter 3 and 4
	threshold = threshold + 1;
	cvPyrMeanShiftFiltering(&frame, &filteredFrame, 10, 35, 3);
	return filteredFrame;
}
