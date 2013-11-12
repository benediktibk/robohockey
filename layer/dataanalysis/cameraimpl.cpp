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
	Mat yellowPic, bluePic, currentPic;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Rect boundRect;
	int white;
	filterFrameAndConvertToHLS();

	inRange(m_fileredFrame, Scalar(21, 40, 50), Scalar(28, 255, 255), yellowPic);
	yellowPic.copyTo(currentPic);
	findContours( currentPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	if (!contours.empty())
	{
		for(unsigned int i = 0; i < contours.size(); i++ )
		{
			white = 0;
			boundRect = boundingRect( Mat(contours[i]));
			if (boundRect.area() > 1500)
			{
				currentPic = yellowPic(boundRect);
				for (int i = 0; i < boundRect.height; ++i) {
					for (int j = 0; j < boundRect.width; j++)
					{
						if (currentPic.at<uchar>(i, j) == 255.0)
							white++;
					}
				}
				if(white > 0.5*boundRect.area())
					cameraObjects.addObject(CameraObject(ColorTypeYellow, boundRect));
			}
		}
		contours.clear();
	}

	inRange(m_fileredFrame, Scalar(95, 40, 40), Scalar(105, 255, 255), bluePic);
	bluePic.copyTo(currentPic);
	findContours( bluePic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	if (!contours.empty())
	{
		for(unsigned int i = 0; i < contours.size(); i++ )
		{
			white = 0;
			boundRect = boundingRect( Mat(contours[i]));
			if (boundRect.area() > 1500)
			{
				currentPic = bluePic(boundRect);
				for (int i = 0; i < boundRect.height; ++i) {
					for (int j = 0; j < boundRect.width; j++)
					{
						if (currentPic.at<uchar>(i, j) == 255.0)
							white++;
					}
				}
				if(white > 0.5*boundRect.area())
					cameraObjects.addObject(CameraObject(ColorTypeYellow, boundRect));
			}
		}
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
