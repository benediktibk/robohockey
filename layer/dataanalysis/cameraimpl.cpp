#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/camera.h"
#include <opencv/cv.h>

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace cv;

CameraImpl::CameraImpl(Hardware::Camera &camera) :
	m_camera(camera)
{ }

CameraObjects CameraImpl::getAllCameraObjects() const
{
	CameraObjects cameraObjects;
	Mat yellowGoalPic, yellowPukPic, bluePukPic;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	filterFrame();

	inRange(m_fileredFrame, cv::Scalar(105, 185, 200), cv::Scalar(130, 215, 240), yellowGoalPic);
	findContours( yellowGoalPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	vector<Rect> boundRect( contours.size() );
	for(unsigned int i = 0; i < contours.size(); i++ )
	   {
		///@todo assert only one yellow goal
		 boundRect[i] = boundingRect( Mat(contours[i]) );
		 cameraObjects.addObject(CameraObject(Common::ColorTypeYellowGoal, boundRect[i]));
	   }

	inRange(m_fileredFrame, cv::Scalar(40, 155, 200), cv::Scalar(80, 195, 240), yellowPukPic);
	findContours( yellowGoalPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	for(unsigned int i = 0; i < contours.size(); i++ )
	   {
		 boundRect[i] = boundingRect( Mat(contours[i]) );
		 cameraObjects.addObject(CameraObject(Common::ColorTypeYellowGoal, boundRect[i]));
	   }

	inRange(m_fileredFrame, cv::Scalar(95, 60, 15), cv::Scalar(135, 100, 55), bluePukPic);
	findContours( yellowGoalPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	for(unsigned int i = 0; i < contours.size(); i++ )
	   {
		 boundRect[i] = boundingRect( Mat(contours[i]) );
		 cameraObjects.addObject(CameraObject(Common::ColorTypeYellowGoal, boundRect[i]));
	   }

	return cameraObjects;
}

bool CameraImpl::isGoalYellow() const
{
	Mat goal;
	int white;
	filterFrame();
	//Filter parameter 2 und 3: untere Grenze (b,g,r), obere Grenze (b,g,r)
	inRange(m_fileredFrame, cv::Scalar(105, 185, 200), cv::Scalar(130, 215, 240), goal);
	Rect range(0, 130, 320, 110);
	goal = goal(range);
	for (int i = 0; i < range.height; ++i) {
		for (int j = 0; j < range.width; j++)
		{
			if (goal.at<uchar>(i, j) == 255.0)
				white++;
		}
	}
	//mehr als 70% der pixel sind weiß
	if(white > 0.7*range.area())
		return true;
	else
		return false;
}

void CameraImpl::filterFrame() const
{
	medianBlur(m_camera.getFrame(), m_fileredFrame, 9);
}
