#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/fielddetector.h"
#include "common/robotposition.h"
#include "common/compare.h"
#include "layer/dataanalysis/odometryimpl.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/dataanalysis/cameraimpl.h"
#include "layer/autonomous/fieldobject.h"
#include "math.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;
using namespace std;

FieldImpl::FieldImpl(DataAnalysis::Odometry &odometry, const DataAnalysis::Lidar &lidar, DataAnalysis::Camera &camera):
	m_odometry(&odometry),
	m_lidar(&lidar),
	m_camera(&camera),
	m_position(new Common::RobotPosition(m_odometry->getCurrentPosition()))
{ }

FieldImpl::~FieldImpl()
{
	delete m_position;
	m_position = 0;

	m_fieldObjects.clear();
}

void FieldImpl::update()
{
	updateWithOdometryData();
	updateWithLidarData();
	updateWithCameraData();
//	tryToFindField();
}

std::vector<FieldObject>& FieldImpl::getAllFieldObjects()
{
	return m_fieldObjects;
}

void FieldImpl::tryToFindField()
{
	vector<Point> &input = getPointsOfObjectsWithDiameterAndColor(0.06, FieldObjectColorGreen);

	FieldDetector detector(input);

	bool result = detector.tryToDetectField();

	if (result)
	{
		cout << "Objects: "<< input.size() <<" Found new Origin!!!" << endl;
		Point newOrigin = detector.getNewOrigin();
		transformCoordinateSystem(newOrigin, detector.getRotation());
	}
	else
		cout << "Objects: "<< input.size() << " Could not detect new Origin." << endl;

	delete &input;


	//return result;
}

void FieldImpl::updateWithLidarData()
{
	const DataAnalysis::LidarObjects &lidarObjects =  m_lidar->getAllObjects(*m_position);
	const vector<DataAnalysis::LidarObject> &objectsInRange = lidarObjects.getObjectsWithDistanceBelow(4);

	removeAllFieldObjectsInVisibleArea();

	for (vector<DataAnalysis::LidarObject>::const_iterator i = objectsInRange.begin(); i != objectsInRange.end(); ++i)
	{
		FieldObject *object = new FieldObject(*i,FieldObjectColorUnknown);
		m_fieldObjects.push_back(*object);
	}
}

void FieldImpl::updateWithOdometryData()
{
	*m_position = m_odometry->getCurrentPosition();
}

void FieldImpl::updateWithCameraData()
{
	//! @todo Use Camera Data!
	const DataAnalysis::CameraObjects &allCameraObjects = m_camera->getAllCameraObjects(*m_position);


	if (m_fieldObjects.size() < allCameraObjects.getObjectCount())
		return;

	for (size_t i = 0; i < allCameraObjects.getObjectCount(); ++i)
	{
		const DataAnalysis::CameraObject &currentObject = allCameraObjects[i];
		FieldObject &nextFieldObject = getNextObjectFromPosition(currentObject.getPosition());

//		cout << "Camera: " << currentObject.getPosition() << " Laser: " << nextFieldObject.getCircle().getCenter() << " delta: " << currentObject.getPosition().distanceTo(nextFieldObject.getCircle().getCenter()) << endl;

		if (currentObject.getPosition().distanceTo(nextFieldObject.getCircle().getCenter()) < 0.1)
		{
			if (currentObject.getColorType() == DataAnalysis::ColorTypeYellow)
				nextFieldObject.setColor(FieldObjectColorYellow);

			else if (currentObject.getColorType() == DataAnalysis::ColorTypeBlue)
				nextFieldObject.setColor(FieldObjectColorBlue);

			else if (currentObject.getColorType() == DataAnalysis::ColorTypeGreen)
				nextFieldObject.setColor(FieldObjectColorGreen);
		}
	}

}

FieldObject &FieldImpl::getNextObjectFromPosition(Point position)
{
	//! @todo Test!
	FieldObject &nextFieldObject = m_fieldObjects.front();
	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		if ( position.distanceTo((*i).getCircle().getCenter()) < position.distanceTo(nextFieldObject.getCircle().getCenter()))
			nextFieldObject = *i;
	}
	return nextFieldObject;
}

void FieldImpl::transformCoordinateSystem(Point &newOrigin, double rotation)
{
	moveCoordinateSystem(newOrigin);
	rotateCoordinateSystem(rotation);
}

void FieldImpl::rotateCoordinateSystem(double alpha)
{
	//! @todo test and implement rotation of coordinate system

	vector<FieldObject> newSystem;

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();
		double currentDiameter = ((*i).getCircle()).getDiameter();
		FieldObjectColor color = (*i).getColor();

		currentCenter.rotate(Angle(alpha));

		newSystem.push_back(FieldObject(Circle(currentCenter, currentDiameter), color));
	}

	Point ownPosition = m_position->getPosition();
	Angle ownOrientation = m_position->getOrientation();

	ownPosition.rotate(Angle(alpha));
	ownOrientation = ownOrientation + Angle(alpha);

	m_position->setPosition(ownPosition);
	m_position->setOrientation(ownOrientation);

	m_odometry->setCurrentPosition(*m_position);

	m_fieldObjects.clear();
	m_fieldObjects = newSystem;

}

void FieldImpl::moveCoordinateSystem(Point &newOrigin)
{
	//! @todo test and implement movement of coordinate system

	vector<FieldObject> newSystem;

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();
		double currentDiameter = ((*i).getCircle()).getDiameter();
		Point newCenter = currentCenter - newOrigin;
		FieldObjectColor color = (*i).getColor();

		newSystem.push_back(FieldObject(Circle(newCenter, currentDiameter), color));
	}

	Point ownPosition = m_position->getPosition();

	ownPosition =  ownPosition - newOrigin;
	m_position->setPosition(ownPosition);

	m_odometry->setCurrentPosition(*m_position);

	m_fieldObjects.clear();
	m_fieldObjects = newSystem;

}

std::vector<Point> &FieldImpl::getPointsOfObjectsWithDiameterAndColor(double , FieldObjectColor )
{
	vector<Point> *resultObjects = new vector<Point>;

	Compare compare(0.02);
	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
//! Deactivated Filter! -> Returns Positions of all Objects!
//		if (compare.isFuzzyEqual(((*i).getCircle()).getDiameter(), diameter) && ((*i).getColor() == color || (*i).getColor() == FieldObjectColorUnknown))
//		{
			resultObjects->push_back(((*i).getCircle()).getCenter());
//		}
	}

	return *resultObjects;
}

void FieldImpl::removeAllFieldObjectsInVisibleArea()
{
	Point referencePoint = m_position->getPosition();
	Point directionVector(1, m_position->getOrientation());
	directionVector.rotate(Angle::getQuarterRotation());

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();

		//! @todo Use a global parameter for distance filtering
		if (Point::isTargetPointRightOfLine(referencePoint, directionVector, currentCenter))
		{
			m_fieldObjects.erase(i);
			i--;
		}
	}
}
