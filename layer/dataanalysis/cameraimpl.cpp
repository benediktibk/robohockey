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
	CameraObjects cameraObjects;
	Mat yellowPic, bluePic;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Rect> boundRect;
	filterFrameAndConvertToHLS();

	inRange(m_fileredFrame, cv::Scalar(20, 100, 50), cv::Scalar(30, 200, 255), yellowPic);
	findContours( yellowPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	if (!contours.empty())
	{
		for(unsigned int i = 0; i < contours.size(); i++ )
		{
			boundRect.push_back(boundingRect( Mat(contours[i])));
			cameraObjects.addObject(CameraObject(ColorTypeYellow, boundRect[i]));
		}
		boundRect.clear();
		contours.clear();
	}

	///@todo find color values for blue objects
	inRange(m_fileredFrame, cv::Scalar(95, 60, 15), cv::Scalar(135, 100, 55), bluePic);
	findContours( bluePic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	if (!contours.empty())
	{
		for(unsigned int i = 0; i < contours.size(); i++ )
		{
			boundRect.push_back(boundingRect( Mat(contours[i])));
			cameraObjects.addObject(CameraObject(ColorTypeYellow, boundRect[i]));
		}
		boundRect.clear();
		contours.clear();
	}

	return cameraObjects;
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
	imwrite("goal.png",goal);
	//mehr als 70% der pixel sind weiß
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
