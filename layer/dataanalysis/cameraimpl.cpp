#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/camera.h"
#include <opencv/cv.h>

using namespace RoboHockey::Layer::DataAnalysis;
using namespace cv;
using namespace std;

CameraImpl::CameraImpl(Hardware::Camera &camera) :
	m_camera(camera)
{ }

CameraObjects CameraImpl::getAllCameraObjects()
{
	filterFrameAndConvertToHLS();
	addObjects(ColorTypeYellow);
	addObjects(ColorTypeBlue);
	addObjects(ColorTypeGreen);

	return m_cameraObjects;
}

bool CameraImpl::isGoalYellow()
{
	Mat goal;
	filterFrameAndConvertToHLS();
	inRange(m_fileredFrame, cv::Scalar(20, 100, 50), cv::Scalar(30, 200, 255), goal);
	Rect range(0, 130, 320, 110);
	goal = goal(range);
	if(countNonZero(goal) > 0.8*range.area())
		return true;
	else
		return false;
}

void CameraImpl::filterFrameAndConvertToHLS()
{
	medianBlur(m_camera.getFrame(), m_fileredFrame, 9);
	cvtColor(m_fileredFrame, m_fileredFrame, CV_BGR2HLS);
}

void CameraImpl::addObjects(ColorType color)
{
	Mat colorPic, currentPic;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Rect boundRect;
	Scalar minValue, maxValue;
	int areaThreshold;

	switch (color) {
	case ColorTypeYellow:
		minValue = Scalar(21, 40, 50);
		maxValue = Scalar(28, 255, 255);
		areaThreshold = 2000;
		break;
	case ColorTypeBlue:
		minValue = Scalar(95, 40, 40);
		maxValue = Scalar(107, 255, 255);
		areaThreshold = 2000;
		break;
	case ColorTypeGreen:
		minValue = Scalar(75, 40, 55);
		maxValue = Scalar(85, 255, 255);
		areaThreshold = 750;
		break;
	default:
		break;
	}

	inRange(m_fileredFrame, minValue, maxValue, colorPic);
	colorPic.copyTo(currentPic);
	findContours(currentPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	if (!contours.empty())
	{
		for(unsigned int i = 0; i < contours.size(); i++ )
		{
			boundRect = boundingRect(Mat(contours[i]));
			if (contourArea(contours[i]) > areaThreshold)
			{
				currentPic = colorPic(boundRect);
				if(countNonZero(currentPic) > 0.9*contourArea(contours[i]))
					//!@todo correct position for Point
					m_cameraObjects.addObject(CameraObject(color, Common::Point(0,0)));
			}
		}
		contours.clear();
	}
}
