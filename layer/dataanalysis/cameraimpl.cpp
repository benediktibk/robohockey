#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/camera.h"
#include <opencv/cv.h>
#include "math.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace cv;
using namespace std;

CameraImpl::CameraImpl(Hardware::Camera &camera) :
	m_camera(camera)
{ }

CameraObjects CameraImpl::getAllCameraObjects(const Common::RobotPosition &position)
{
	m_ownPosition = position;
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
	Rect range(103, 180, 114, 60);
	goal = goal(range);
	if(countNonZero(goal) > 0.8*range.area())
		return true;
	else
		return false;
}

void CameraImpl::filterFrameAndConvertToHLS()
{
	m_fileredFrame = m_camera.getFrame();
	cv::Point2f destinationPoints[4];
	cv::Point2f sourcePoints[4];
	Mat transform_matrix;

	sourcePoints[0] = Point2f(0,0);
	sourcePoints[1] = Point2f(320,0);
	sourcePoints[2] = Point2f(320,240);
	sourcePoints[3] = Point2f(0,240);

	destinationPoints[0] = Point2f(0,0);
	destinationPoints[1] = Point2f(320,0);
	destinationPoints[2] = Point2f(217,240);
	destinationPoints[3] = Point2f(103,240);

	transform_matrix = getPerspectiveTransform(sourcePoints, destinationPoints);
	cv::warpPerspective(m_fileredFrame, m_fileredFrame, transform_matrix, cv::Size(320,240));

	medianBlur(m_fileredFrame, m_fileredFrame, 9);
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
	Point objectFootPixel;

	switch (color) {
	case ColorTypeYellow:
		minValue = Scalar(18, 40, 50);
		maxValue = Scalar(28, 255, 255);
		areaThreshold = 1500;
		break;
	case ColorTypeBlue:
		minValue = Scalar(95, 40, 40);
		maxValue = Scalar(107, 255, 255);
		areaThreshold = 1500;
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
				{
					objectFootPixel.x = boundRect.x + 0.5*boundRect.width;
					objectFootPixel.y = boundRect.y + boundRect.height;
					m_cameraObjects.addObject(CameraObject(color, getCalculatedPosition(objectFootPixel)));
				}
			}
		}
		contours.clear();
	}
}

const RoboHockey::Common::Point CameraImpl::getCalculatedPosition(Point pixel) const
{
	Point robotMatPosition(160,240);
	Common::Point objectPosition;

	pixel.x = pixel.x -robotMatPosition.x;
	pixel.y = robotMatPosition.y - pixel.y;
	objectPosition.setX(pixel.x * (1.9/320));
	objectPosition.setY(pixel.y * (1.66/240) + 0.34);

	objectPosition.rotate(Common::Angle(-0.5 * M_PI) + m_ownPosition.getOrientation());
	objectPosition = objectPosition + m_ownPosition.getPosition();

	return objectPosition;
}
