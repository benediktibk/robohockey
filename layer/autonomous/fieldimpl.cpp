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
}

vector<FieldObject> FieldImpl::getAllFieldObjects()
{
	return m_fieldObjects;
}

vector<Circle> FieldImpl::getAllObstacles()
{
	vector<Circle> obstacles;
	obstacles.reserve(m_fieldObjects.size());

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
		obstacles.push_back(i->getCircle());

	return obstacles;
}

bool FieldImpl::calibratePosition()
{
	vector<Point> &input = getPointsOfObjectsWithDiameterAndColor(0.06, FieldObjectColorGreen);

	FieldDetector detector(input);

	bool result = detector.tryToDetectField();

	if (result)
	{
		Point newOrigin = detector.getNewOrigin();
		transformCoordinateSystem(newOrigin, detector.getRotation());
		cout << "Found borderstones -> System transformed." << endl;
	} else
		cout << "Didn't find enough borderstones." << endl;

	delete &input;

	return result;
}

void FieldImpl::updateWithLidarData()
{
	const DataAnalysis::LidarObjects &lidarObjects =  m_lidar->getAllObjects(*m_position);
	const vector<DataAnalysis::LidarObject> &objectsInRange = lidarObjects.getObjectsWithDistanceBelow(6);

	vector<FieldObject> inVisibleArea = moveAllFieldObjectsInVisibleAreaToTemporaryVector();

	for (vector<DataAnalysis::LidarObject>::const_iterator i = objectsInRange.begin(); i != objectsInRange.end(); ++i)
	{
		if (inVisibleArea.size() != 0)
		{
			vector<FieldObject>::iterator currentObject = getNextObjectFromPosition(inVisibleArea, (*i).getCenter());

			if ( tryToMergeLidarAndFieldObject(*currentObject, *i))
			{
				inVisibleArea.erase(currentObject);
				continue;
			}
		}
		FieldObject object(*i,FieldObjectColorUnknown);
		m_fieldObjects.push_back(object);
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


	if (m_fieldObjects.size() == 0 || allCameraObjects.getObjectCount() == 0)
		return;

	for (size_t i = 0; i < allCameraObjects.getObjectCount(); ++i)
	{
		const DataAnalysis::CameraObject &currentObject = allCameraObjects[i];
		FieldObject &nextFieldObject = getNextObjectFromPosition(currentObject.getPosition());

//		cout << "Camera: " << currentObject.getPosition() << " Laser: " << nextFieldObject.getCircle().getCenter() << " delta: " << currentObject.getPosition().distanceTo(nextFieldObject.getCircle().getCenter()) << endl;

		if (currentObject.getPosition().distanceTo(nextFieldObject.getCircle().getCenter()) < 0.07)
		{
			nextFieldObject.setColor(currentObject.getColor());
			Circle circle = nextFieldObject.getCircle();

			if (currentObject.getColor() == FieldObjectColorBlue || currentObject.getColor() == FieldObjectColorYellow)
			{
				circle.setDiameter(0.12);
				nextFieldObject.setCircle(circle);
			} else if (currentObject.getColor() == FieldObjectColorGreen)
			{
				circle.setDiameter(0.06);
				nextFieldObject.setCircle(circle);
			}
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

vector<FieldObject>::iterator FieldImpl::getNextObjectFromPosition(std::vector<FieldObject> &fieldObjects, Point position)
{
	vector<FieldObject>::iterator result = fieldObjects.begin();

	for (vector<FieldObject>::iterator i = fieldObjects.begin(); i != fieldObjects.end(); ++i)
	{
		if ( position.distanceTo((*i).getCircle().getCenter()) < position.distanceTo((*result).getCircle().getCenter()))
			result = i;
	}

	return result;
}

bool FieldImpl::tryToMergeLidarAndFieldObject(FieldObject &fieldObject, const DataAnalysis::LidarObject &lidarObject)
{
	Compare positionCompare(0.09);
	Point newCenter;
	double diameter = 0.0;

	if ( positionCompare.isFuzzyEqual( fieldObject.getCircle().getCenter(), lidarObject.getCenter() ) )
	{
		newCenter  = ( fieldObject.getCircle().getCenter() + lidarObject.getCenter() ) * 0.5;
		diameter = fieldObject.getCircle().getDiameter();

		if (fieldObject.getColor() == FieldObjectColorUnknown)
			diameter = 0.5 * (fieldObject.getCircle().getDiameter() + lidarObject.getDiameter());

		m_fieldObjects.push_back(FieldObject( Circle(newCenter, diameter), fieldObject.getColor()));
		return true;
	}

	return false;
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
	assert(*m_position == m_odometry->getCurrentPosition());

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

	Point newCenter =  m_position->getPosition() - newOrigin;
	m_position->setPosition(newCenter);

	m_odometry->setCurrentPosition(*m_position);
	assert(*m_position == m_odometry->getCurrentPosition());

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

vector<FieldObject> FieldImpl::moveAllFieldObjectsInVisibleAreaToTemporaryVector()
{
	vector<FieldObject> result;
	Point referencePoint = m_position->getPosition();
	Point directionVector(1, m_position->getOrientation());
	directionVector.rotate(Angle::getQuarterRotation());

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();

		if (Point::isTargetPointRightOfLine(referencePoint, directionVector, currentCenter))
		{
			m_fieldObjects.erase(i);
			result.push_back(*i);
			i--;
		}
	}

	return result;
}
