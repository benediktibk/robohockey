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

Mat CameraImpl::getSmoothFrame()
{
	Mat frame = m_camera.getFrame();
	Mat smoothFrame = frame;

	cvSmooth(&frame, &smoothFrame, CV_MEDIAN, 9 , 9);
	return smoothFrame;
}

Mat CameraImpl::getFilteredFrame(unsigned int threshold)
{
	//CvMemStorage* storage = cvCreateMemStorage(0);
	//CvSeq* comp = NULL;
	Mat filteredFrame = getSmoothFrame();

	//threshold used for building
	threshold = threshold + 1;
	//cvPyrSegmentation(getSmoothFrame(), filteredFrame, storage, &comp, 4, 200, 50);
	return filteredFrame;
}
