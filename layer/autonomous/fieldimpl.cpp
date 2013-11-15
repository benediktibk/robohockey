#include "layer/autonomous/fieldimpl.h"
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

FieldImpl::FieldImpl(DataAnalysis::Odometry &odometry, const DataAnalysis::Lidar &lidar, const DataAnalysis::Camera &camera):
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

std::vector<FieldObject>& FieldImpl::getAllFieldObjects()
{
	return m_fieldObjects;
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

		Point newCenter;
		newCenter.setX( cos(alpha)*currentCenter.getX() - sin(alpha)*currentCenter.getY() );
		newCenter.setY( sin(alpha)*currentCenter.getX() + cos(alpha)*currentCenter.getY() );

		newSystem.push_back(FieldObject(Circle(newCenter, currentDiameter), color));
	}

	m_fieldObjects.clear();
	m_fieldObjects = newSystem;

}

void FieldImpl::moveCoordinateSystem(Point &newOrigin)
{
	//! @todo test and implement movment of coordinate system

	vector<FieldObject> newSystem;

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();
		double currentDiameter = ((*i).getCircle()).getDiameter();
		Point newCenter = newOrigin - currentCenter;
		FieldObjectColor color = (*i).getColor();

		newSystem.push_back(FieldObject(Circle(newCenter, currentDiameter), color));
	}

	m_fieldObjects.clear();
	m_fieldObjects = newSystem;

}

std::vector<Point> &FieldImpl::getPointsOfObjectsWithDiameterAndColor(double diameter, FieldObjectColor color)
{
	vector<Point> *resultObjects = new vector<Point>;

	Compare compare(0.02);
	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		if (compare.isFuzzyEqual(((*i).getCircle()).getDiameter(), diameter) && (*i).getColor() == color)
		{
			resultObjects->push_back(((*i).getCircle()).getCenter());
		}
	}

	return *resultObjects;
}

void FieldImpl::removeAllFieldObjectsInVisibleArea()
{
	Point directionVector;
	Point referencePoint = m_position->getPosition();
	Angle orientation = m_position->getOrientation();

	Angle alpha = Angle::getQuarterRotation() - orientation;
	directionVector.setX(-(cos(alpha.getValueBetweenMinusPiAndPi())));
	directionVector.setY(sin(alpha.getValueBetweenMinusPiAndPi()));

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
