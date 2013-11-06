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

	cvSmooth(&frame, &smoothFrame, CV_MEDIAN, 9 , 9);
	return smoothFrame;
}

Mat CameraImpl::getFilteredFrame(unsigned int threshold)
{
	Mat frame = getSmoothFrame();
	Mat filteredFrame = frame;

	//threshold used for building
	threshold = threshold + 1;
	cvPyrMeanShiftFiltering(&frame, &filteredFrame, 10, 35, 3);
	return filteredFrame;
}
