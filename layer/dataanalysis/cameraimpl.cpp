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
	Mat goal;
	int withe;
	//Filter parameter 2 und 3: untere Grenze (b,g,r), obere Grenze (b,g,r)
	inRange(m_fileredFrame, cv::Scalar(105, 185, 200), cv::Scalar(130, 215, 240), goal);
	Rect range(0, 130, 320, 110);
	goal = goal(range);
	for (int i = 0; i < range.height; ++i) {
		for (int j = 0; j < range.width; j++)
		{
			if (goal.at<uchar>(i, j) == 255.0)
				withe++;
		}
	}
	//mehr als 70% der pixel sind weiß
	if(withe > 0.7*range.area())
		return true;
	else
		return false;
}

void CameraImpl::filterFrame()
{
	medianBlur(m_camera.getFrame(), m_fileredFrame, 9);
}
