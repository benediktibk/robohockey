#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/camera.h"
#include <opencv/cv.h>

using namespace RoboHockey::Layer;
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
	int white = 0;
	filterFrameAndConvertToHLS();
	inRange(m_fileredFrame, cv::Scalar(20, 100, 50), cv::Scalar(30, 200, 255), goal);
	Rect range(0, 130, 320, 110);
	goal = goal(range);
	for (int i = 0; i < range.height; ++i) {
		for (int j = 0; j < range.width; j++)
		{
			if (goal.at<uchar>(i, j) == 255.0)
				white++;
		}
	}
	if(white > 0.7*range.area())
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
	int white;
	Scalar minValue, maxValue;

	switch (color) {
	case ColorTypeYellow:
		minValue = Scalar(21, 40, 50);
		maxValue = Scalar(28, 255, 255);
		break;
	case ColorTypeBlue:
		minValue = Scalar(95, 40, 40);
		maxValue = Scalar(107, 255, 255);
		break;
	case ColorTypeGreen:
		//!@todo find green values
		minValue = Scalar(1, 1, 1);
		maxValue = Scalar(1, 255, 255);
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
			white = 0;
			boundRect = boundingRect( Mat(contours[i]));
			if (boundRect.area() > 1500)
			{
				currentPic = colorPic(boundRect);
				for (int i = 0; i < boundRect.height; ++i) {
					for (int j = 0; j < boundRect.width; j++)
					{
						if (currentPic.at<uchar>(i, j) == 255.0)
							white++;
					}
				}
				if(white > 0.45*boundRect.area())
					m_cameraObjects.addObject(CameraObject(color, boundRect));
			}
		}
		contours.clear();
	}
}
