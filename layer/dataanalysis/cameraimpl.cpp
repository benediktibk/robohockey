#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/camera.h"
#include <opencv/cv.h>
#include "math.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace cv;
using namespace std;

CameraImpl::CameraImpl(Hardware::Camera &camera) :
	m_camera(camera)
{ }

CameraObjects CameraImpl::getAllCameraObjects(const RobotPosition &position)
{
	m_cameraObjects.clear();

	if (m_camera.isValid())
	{
		m_ownPosition = position;
		filterFrameAndConvertToHLS();
		addObjects(FieldColorYellow);
		addObjects(FieldColorBlue);
		addObjects(FieldColorGreen);
	}

	return m_cameraObjects;
}

double CameraImpl::getProbabilityForYellowGoal()
{
	assert(m_camera.isValid());
	Mat goal;
	filterFrameAndConvertToHLS();
	inRange(m_filteredFrame, Scalar(20, 100, 50), Scalar(30, 200, 255), goal);
	Rect range(103, 180, 114, 60);
	goal = goal(range);

	return (static_cast<double>(countNonZero(goal))/static_cast<double>(range.area()));
}

double CameraImpl::getProbabilityForBlueGoal()
{
	assert(m_camera.isValid());
	Mat goal;
	filterFrameAndConvertToHLS();
	inRange(m_filteredFrame, Scalar(95, 20, 50), Scalar(107, 255, 255), goal);
	Rect range(103, 180, 114, 60);
	goal = goal(range);

	return (static_cast<double>(countNonZero(goal))/static_cast<double>(range.area()));
}

double CameraImpl::getProbabilityForCollectedYellowPuck()
{
	assert(m_camera.isValid());
	Mat puck;
	filterFrameAndConvertToHLS();
	inRange(m_filteredFrame, Scalar(20, 20, 50), Scalar(32, 255, 255), puck);
	Rect range(155, 235, 13, 5);
	puck = puck(range);

	return (static_cast<double>(countNonZero(puck))/static_cast<double>(range.area()));
}

double CameraImpl::getProbabilityForCollectedBluePuck()
{
	assert(m_camera.isValid());
	Mat puck;
	filterFrameAndConvertToHLS();
	inRange(m_filteredFrame, Scalar(95, 20, 40), Scalar(110, 255, 255), puck);
	Rect range(155, 235, 13, 5);
	puck = puck(range);

	return (static_cast<double>(countNonZero(puck))/static_cast<double>(range.area()));
}


void CameraImpl::filterFrameAndConvertToHLS()
{
	m_filteredFrame = m_camera.getFrame();
	Point2f destinationPoints[4];
	Point2f sourcePoints[4];
	Mat transformationMatrix;
	Mat temp;

	sourcePoints[0] = Point2f(0,0);
	sourcePoints[1] = Point2f(320,0);
	sourcePoints[2] = Point2f(320,240);
	sourcePoints[3] = Point2f(0,240);

	destinationPoints[0] = Point2f(0,0);
	destinationPoints[1] = Point2f(320,0);
	destinationPoints[2] = Point2f(217,240);
	destinationPoints[3] = Point2f(103,240);

	temp = m_filteredFrame.clone();
	transformationMatrix = getPerspectiveTransform(sourcePoints, destinationPoints);
	warpPerspective(temp, m_filteredFrame, transformationMatrix, Size(320,240));

	medianBlur(m_filteredFrame, m_filteredFrame, 9);
	cvtColor(m_filteredFrame, m_filteredFrame, CV_BGR2HLS);
}

void CameraImpl::addObjects(FieldColor color)
{
	Mat colorPic, currentPic;
	vector< vector<cv::Point> > contours;
	vector<Vec4i> hierarchy;
	Rect boundRect;
	Scalar minValue, maxValue;
	int areaThreshold = 0;
	cv::Point objectFootPixel;
	double distanceToCenter = 0;

	switch (color)
	{
	case FieldColorYellow:
		minValue = Scalar(18, 20, 50);
		maxValue = Scalar(28, 255, 255);
		areaThreshold = 1500;
		distanceToCenter = 0.06;
		break;
	case FieldColorBlue:
		minValue = Scalar(95, 20, 40);
		maxValue = Scalar(107, 255, 255);
		areaThreshold = 1500;
		distanceToCenter = 0.06;
		break;
	case FieldColorGreen:
		minValue = Scalar(75, 20, 55);
		maxValue = Scalar(85, 255, 255);
		areaThreshold = 750;
		distanceToCenter = 0.03;
		break;
	case FieldColorUnknown:
		break;
	}

	inRange(m_filteredFrame, minValue, maxValue, colorPic);
	colorPic.copyTo(currentPic);
	findContours(currentPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	if (!contours.empty())
	{
		for(unsigned int i = 0; i < contours.size(); i++)
		{
			boundRect = boundingRect(Mat(contours[i]));
			if (contourArea(contours[i]) > areaThreshold)
			{
				currentPic = colorPic(boundRect);
				if(countNonZero(currentPic) > 0.9*contourArea(contours[i]))
				{
					objectFootPixel = cv::Point(0,0);
					for (unsigned int j = 0; j < contours[i].size(); j++)
					{
						if(objectFootPixel.y < contours[i][j].y)
						{
							objectFootPixel.x = contours[i][j].x;
							objectFootPixel.y = contours[i][j].y;
						}
					}
					m_cameraObjects.addObject(CameraObject(color, getCalculatedPosition(objectFootPixel, distanceToCenter)));
				}
			}
		}
		contours.clear();
	}
}

const RoboHockey::Common::Point CameraImpl::getCalculatedPosition(cv::Point pixel, double distanceToCenter) const
{
	cv::Point robotMatPosition(160,240);
	Common::Point objectPosition;

	pixel.x = pixel.x - robotMatPosition.x;
	pixel.y = robotMatPosition.y - pixel.y;
	objectPosition.setX(pixel.x * (1.9/320));
	objectPosition.setY(pixel.y * (1.66/240) + 0.34 + distanceToCenter);

	objectPosition.rotate(Angle(-0.5 * M_PI) + m_ownPosition.getOrientation());
	objectPosition = objectPosition + m_ownPosition.getPosition();

	return objectPosition;
}
