#include "layer/autonomous/fieldimpl.h"
#include "common/robotposition.h"
#include "layer/dataanalysis/odometryimpl.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/dataanalysis/cameraimpl.h"
#include "layer/autonomous/fieldobject.h"
#include "math.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;
using namespace std;

FieldImpl::FieldImpl(DataAnalysis::OdometryImpl &odometry, DataAnalysis::LidarImpl &lidar, DataAnalysis::CameraImpl &camera):
	m_odometry(&odometry),
	m_lidar(&lidar),
	m_camera(&camera),
	m_position(new Common::RobotPosition(m_odometry->getCurrentPosition()))
{

}

FieldImpl::~FieldImpl()
{
	delete m_position;
	m_position = 0;
}

void FieldImpl::update()
{
	updateWithOdometryData();
	updateWithLidarData();
}

std::vector<FieldObject>& FieldImpl::getAllFieldObjects()
{
	return m_fieldObjects;
}

void FieldImpl::updateWithLidarData()
{
	DataAnalysis::LidarObjects lidarObjects =  m_lidar->getAllObjects(Point(m_position->getX(), m_position->getY()), m_position->getOrientation());
	vector<DataAnalysis::LidarObject> objectsInRange = lidarObjects.getObjectsWithDistanceBelow(5);

	//! @todo: Update only visible range of objects.
	m_fieldObjects.clear();

	for (vector<DataAnalysis::LidarObject>::iterator i = objectsInRange.begin(); i != objectsInRange.end(); ++i)
	{
		FieldObject *object = new FieldObject(*i,FieldObjectColorUnknown);
		m_fieldObjects.push_back(*object);
	}
}

void FieldImpl::updateWithOdometryData()
{
	Point currentPosition = m_odometry->getCurrentPosition();
	m_position->setX(currentPosition.getX());
	m_position->setY(currentPosition.getY());
	m_position->setOrientation(m_odometry->getCurrentOrientation());
}

void FieldImpl::transformCoordinateSystem(Point &, double )
{
	//! @todo: Transform all Objects to new Coordinate Origin
}

std::vector<FieldObject> &FieldImpl::getAllFieldObjectsInVisibleArea()
{
	vector<FieldObject> *visibleObjects = new vector<FieldObject>;
	Point directionVector;
	Point referencePoint(m_position->getX(), m_position->getY());
	double orientation = m_position->getOrientation();
	double pi = M_PI;

	double alpha = (0.5*pi) - orientation;
	directionVector.setX(-(cos(alpha)));
	directionVector.setY(sin(alpha));


	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();

		//! @todo: Use a global parameter for distance filtering
		if (isTargetPointRightOfLineWithParameters(referencePoint, directionVector, currentCenter) && currentCenter.distanceTo(referencePoint) < 3)
		{
			visibleObjects->push_back(*i);
		}

	}

	return *visibleObjects;
}

bool FieldImpl::isTargetPointRightOfLineWithParameters(Point &referencePoint, Point &directionVector, Point &target)
{
	return 0 < (directionVector.getY()*(target.getX() - referencePoint.getX()) - directionVector.getX()*(target.getY() - referencePoint.getY()));
}
