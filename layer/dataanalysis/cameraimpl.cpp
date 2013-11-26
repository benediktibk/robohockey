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
	m_cameraObjects.clear();

	if (m_camera.isValid())
	{
		m_ownPosition = position;
		filterFrameAndConvertToHLS();
		addObjects(Common::FieldObjectColorYellow);
		addObjects(Common::FieldObjectColorBlue);
		addObjects(Common::FieldObjectColorGreen);
	}

	return m_cameraObjects;
}

double CameraImpl::getProbabilityForYellowGoal()
{
	assert(m_camera.isValid());
	Mat goal;
	filterFrameAndConvertToHLS();
	inRange(m_filteredFrame, cv::Scalar(20, 100, 50), cv::Scalar(30, 200, 255), goal);
	Rect range(103, 180, 114, 60);
	goal = goal(range);
	return (static_cast<double>(countNonZero(goal))/static_cast<double>(range.area()));
}


void CameraImpl::filterFrameAndConvertToHLS()
{
	m_filteredFrame = m_camera.getFrame();
	cv::Point2f destinationPoints[4];
	cv::Point2f sourcePoints[4];
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
	cv::warpPerspective(temp, m_filteredFrame, transformationMatrix, cv::Size(320,240));

	medianBlur(m_filteredFrame, m_filteredFrame, 9);
	cvtColor(m_filteredFrame, m_filteredFrame, CV_BGR2HLS);
}

void CameraImpl::addObjects(Common::FieldObjectColor color)
{
	Mat colorPic, currentPic;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Rect boundRect;
	Scalar minValue, maxValue;
	int areaThreshold;
	Point objectFootPixel;
	double distanceToCenter;

	switch (color) {
	case Common::FieldObjectColorYellow:
		minValue = Scalar(18, 20, 50);
		maxValue = Scalar(28, 255, 255);
		areaThreshold = 1500;
		distanceToCenter = 0.06;
		break;
	case Common::FieldObjectColorBlue:
		minValue = Scalar(95, 20, 40);
		maxValue = Scalar(107, 255, 255);
		areaThreshold = 1500;
		distanceToCenter = 0.06;
		break;
	case Common::FieldObjectColorGreen:
		minValue = Scalar(75, 20, 55);
		maxValue = Scalar(85, 255, 255);
		areaThreshold = 750;
		distanceToCenter = 0.03;
		break;
	default:
		break;
	}

	inRange(m_filteredFrame, minValue, maxValue, colorPic);
	colorPic.copyTo(currentPic);
	findContours(currentPic, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
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
					objectFootPixel = Point(0,0);
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

const RoboHockey::Common::Point CameraImpl::getCalculatedPosition(Point pixel, double distanceToCenter) const
{
	Point robotMatPosition(160,240);
	Common::Point objectPosition;

	pixel.x = pixel.x - robotMatPosition.x;
	pixel.y = robotMatPosition.y - pixel.y;
	objectPosition.setX(pixel.x * (1.9/320));
	objectPosition.setY(pixel.y * (1.66/240) + 0.34 + distanceToCenter);

	objectPosition.rotate(Common::Angle(-0.5 * M_PI) + m_ownPosition.getOrientation());
	objectPosition = objectPosition + m_ownPosition.getPosition();

	return objectPosition;
}
