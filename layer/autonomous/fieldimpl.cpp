#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/fieldobject.h"
#include "layer/autonomous/fielddetector.h"
#include "layer/autonomous/fieldobjectdistancecompare.h"
#include "layer/autonomous/robot.h"
#include "layer/dataanalysis/lidar.h"
#include "layer/dataanalysis/camera.h"
#include "layer/dataanalysis/odometry.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include <math.h>
#include <algorithm>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldImpl::FieldImpl(DataAnalysis::Odometry &odometry, const DataAnalysis::Lidar &lidar, DataAnalysis::Camera &camera, Robot &autonomousRobot):
	m_odometry(&odometry),
	m_lidar(&lidar),
	m_camera(&camera),
	m_robot(&autonomousRobot),
	m_position(new Common::RobotPosition(m_odometry->getCurrentPosition())),
	m_fieldState(FieldStateUnknownPosition),
	m_numberOfPucksChanged(false),
	m_teamColor(FieldColorUnknown)
{ }

FieldImpl::~FieldImpl()
{
	delete m_position;
	m_position = 0;

	m_fieldObjects.clear();
}

void FieldImpl::update()
{
	m_numberOfPucksChanged = false;
	updateWithOdometryData();

	if (!m_robot->isRotating())
	{
		updateWithLidarData();
		if (!m_robot->isMoving())
			updateWithCameraData();
		updateObstacles();
	}

    updateAchievedGoals();
    updateHiddenPucks();
}

const vector<FieldObject> &FieldImpl::getAllFieldObjects() const
{
	return m_fieldObjects;
}

const vector<Circle> &FieldImpl::getAllSoftObstacles() const
{
	return m_softObstacles;
}

const vector<Circle> &FieldImpl::getAllHardObstacles() const
{
	return m_hardObstacles;
}

vector<FieldObject> FieldImpl::getObjectsWithColorOrderdByDistance(FieldColor color, const Point &position) const
{
	vector<FieldObject> result = getObjectsWithColor(color);
	FieldObjectDistanceCompare compare(position);
	sort(result.begin(), result.end(), compare);
	return result;
}

bool FieldImpl::calibratePosition()
{
	RobotPosition newOrigin = getNewOriginFromFieldDetection();
	Point newOriginPoint = newOrigin.getPosition();

	bool result = !(newOrigin.getPosition() == Point::zero()) || !(newOrigin.getOrientation().getValueBetweenMinusPiAndPi() == 0.0);

	if (result)
		transformCoordinateSystem(newOriginPoint, newOrigin.getOrientation().getValueBetweenMinusPiAndPi());

	return result;
}

unsigned int FieldImpl::getNumberOfAchievedGoals()
{
	return m_achievedGoals;
}

unsigned int FieldImpl::getNumberOfHiddenPucks()
{
	return m_hiddenPucks;
}

bool FieldImpl::isPointInsideField(const Point &point) const
{
	return isPointFuzzyInsideField(point, 0.0);
}

bool FieldImpl::isCalibrated() const
{
	return m_fieldState == FieldStateCalibrated;
}

FieldColor FieldImpl::getOwnTeamColor() const
{
    return m_teamColor;
}

FieldColor FieldImpl::getEnemyTeamColor() const
{
    if (m_teamColor == FieldColorYellow)
        return FieldColorBlue;
    else
        return FieldColorYellow;
}

void FieldImpl::detectTeamColorWithGoalInFront()
{
	assert(m_teamColor == FieldColorUnknown);
	Compare compare(0.10);

	double blueGoal = m_camera->getProbabilityForBlueGoal();
	double yellowGoal = m_camera->getProbabilityForYellowGoal();

	if(compare.isStrictFuzzyGreater(blueGoal, yellowGoal))
		m_teamColor = FieldColorBlue;
	else if (compare.isStrictFuzzyGreater(yellowGoal, blueGoal))
		m_teamColor = FieldColorYellow;
}

bool FieldImpl::numberOfPucksChanged() const
{
	return m_numberOfPucksChanged;
}

std::list<RobotPosition> FieldImpl::getTargetsForGoalDetection() const
{
	list<RobotPosition> targetList;
	targetList.push_back(RobotPosition(Point(5.0/6.0 + 0.34,1.5), Angle::getHalfRotation()));

	return targetList;
}

std::list<RobotPosition> FieldImpl::getTargetsForScoringGoals() const
{
	list<RobotPosition> targetList;

	targetList.push_front(RobotPosition( Point(5 - 5.0/8.0 - 0.14, 0.9), Angle() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0 + 0.14, 0.9), Angle::getHalfRotation() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 0.9 + 0.14), Angle::getQuarterRotation() *3 ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 0.9 - 0.14), Angle::getQuarterRotation() ));

	targetList.push_front(RobotPosition( Point(5 - 5.0/8.0 - 0.14, 1.9), Angle() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0 + 0.14, 1.9), Angle::getHalfRotation() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.9 + 0.14), Angle::getQuarterRotation() *3 ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.9 - 0.14), Angle::getQuarterRotation() ));

	targetList.push_front(RobotPosition( Point(5 - 5.0/8.0 - 0.14, 1.5), Angle() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0 + 0.14, 1.5), Angle::getHalfRotation() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.5 + 0.14), Angle::getQuarterRotation() *3 ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.5 - 0.14), Angle::getQuarterRotation() ));

	return targetList;
}

std::list<RobotPosition> FieldImpl::getTargetsForFinalPosition() const
{
	list<RobotPosition> targetList;
	//! @todo maybe we should make these points dependend on the fieldobjects.
	targetList.push_back(RobotPosition( Point(4, 0.5), Angle::getQuarterRotation() + Angle::getEighthRotation() ));
	targetList.push_back(RobotPosition( Point(4, 2.5), Angle::getHalfRotation() + Angle::getEighthRotation() ));

	return targetList;
}

std::list<RobotPosition> FieldImpl::getTargetsForSearchingPucks() const
{
	vector<RobotPosition> targetVector;
	list<RobotPosition> targetList(10);

	targetVector.push_back(RobotPosition( Point(1.4, 0.6), Angle()));
	targetVector.push_back(RobotPosition( Point(1.4, 2.4), Angle()));
	targetVector.push_back(RobotPosition( Point(2.0, 1.0), Angle()));
	targetVector.push_back(RobotPosition( Point(2.0, 2.0), Angle()));
	targetVector.push_back(RobotPosition( Point(2.5, 2.2), Angle::getQuarterRotation() * 3));
	targetVector.push_back(RobotPosition( Point(2.5, 2.2), Angle()));
	targetVector.push_back(RobotPosition( Point(2.5, 0.8), Angle()));
	targetVector.push_back(RobotPosition( Point(2.5, 0.8), Angle::getQuarterRotation()));
	targetVector.push_back(RobotPosition( Point(3.0, 1.5), Angle::getEighthRotation() + Angle::getQuarterRotation()));
	targetVector.push_back(RobotPosition( Point(3.0, 1.5), Angle::getHalfRotation() + Angle::getQuarterRotation()));

	random_shuffle(targetVector.begin(), targetVector.end());

	copy(targetVector.begin(), targetVector.end(), targetList.begin());

	return targetList;
}

std::list<RobotPosition> FieldImpl::getTargetsForHidingEnemyPucks() const
{
	return list<RobotPosition>();
}

std::list<RobotPosition> FieldImpl::getTargetsForCollectingOnePuck() const
{
	return list<RobotPosition>();
}

void FieldImpl::setTrueTeamColor(FieldColor trueTeamColor)
{
	assert(trueTeamColor != FieldColorUnknown);
	assert(trueTeamColor != FieldColorGreen);

	m_teamColor = trueTeamColor;
}

RobotPosition FieldImpl::getNewOriginFromFieldDetection()
{
	vector<Point> *input = getPointsOfObjectsWithDiameterAndColor(0.06, FieldColorGreen);

	FieldDetector detector(m_position->getPosition(), *input);

	bool result = detector.tryToDetectField();

	Point newOrigin;
	double rotation = 0.0;

	if (result)
	{
		newOrigin = detector.getNewOrigin();
		rotation = detector.getRotation();
	}

	delete input;

	return RobotPosition( newOrigin, Angle(rotation) );
}

void FieldImpl::transformFieldToNewOrigin(const RobotPosition newOrigin)
{
	Point newOriginPoint = newOrigin.getPosition();
	transformCoordinateSystem(newOriginPoint, newOrigin.getOrientation().getValueBetweenMinusPiAndPi());
}

void FieldImpl::updateWithLidarData()
{
	const DataAnalysis::LidarObjects &lidarObjects =  m_lidar->getAllObjects(*m_position);
	const vector<DataAnalysis::LidarObject> &objectsInRange = lidarObjects.getObjectsWithDistanceBelow(6);

	vector<FieldObject> inVisibleArea = moveAllFieldObjectsInVisibleAreaToTemporaryVector();

	for (vector<DataAnalysis::LidarObject>::const_iterator i = objectsInRange.begin(); i != objectsInRange.end(); ++i)
	{
		if (!isPointFuzzyInsideField((*i).getCenter(), 0.5))
			continue;

		if (inVisibleArea.size() != 0)
		{
			vector<FieldObject>::iterator currentObject = getNextObjectFromPosition(inVisibleArea, (*i).getCenter());

			if (tryToMergeLidarAndFieldObject(*currentObject, *i))
			{
				inVisibleArea.erase(currentObject);
				continue;
			}
		}

		FieldObject object(*i, FieldColorUnknown);
		m_fieldObjects.push_back(object);
	}

	for (vector<FieldObject>::const_iterator i = inVisibleArea.begin(); i != inVisibleArea.end(); ++i)
	{
		if ((*i).getColor() != FieldColorUnknown)
		{
			m_numberOfPucksChanged = true;
			break;
		}
	}
}

void FieldImpl::updateWithOdometryData()
{
	*m_position = m_odometry->getCurrentPosition();
}

void FieldImpl::updateWithCameraData()
{
	const DataAnalysis::CameraObjects &allCameraObjects = m_camera->getAllCameraObjects(*m_position);

	if (m_fieldObjects.size() == 0 || allCameraObjects.getObjectCount() == 0)
		return;

	for (size_t i = 0; i < allCameraObjects.getObjectCount(); ++i)
	{
		const DataAnalysis::CameraObject &currentObject = allCameraObjects[i];

		FieldObject* nextFieldObject = &getNextObjectFromPosition(currentObject.getPosition());

		if (currentObject.getPosition().distanceTo(nextFieldObject->getCircle().getCenter()) < 0.07)
		{
			if (nextFieldObject->getColor() != currentObject.getColor())
				m_numberOfPucksChanged = true;

			nextFieldObject->setColor(currentObject.getColor());
			Circle circle = nextFieldObject->getCircle();

			if (currentObject.getColor() == FieldColorBlue || currentObject.getColor() == FieldColorYellow)
			{
				circle.setDiameter(0.12);
				nextFieldObject->setCircle(circle);
			}
			else if (currentObject.getColor() == FieldColorGreen)
			{
				circle.setDiameter(0.06);
				nextFieldObject->setCircle(circle);
			}
		}
	}
}

void FieldImpl::updateObstacles()
{
	m_softObstacles.clear();
	m_hardObstacles.clear();
	m_softObstacles.reserve(m_fieldObjects.size());
	m_hardObstacles.reserve(m_fieldObjects.size());

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		const FieldObject &fieldObject = *i;
		const Circle &fieldObjectCircle = fieldObject.getCircle();

		if (fieldObject.getColor() == FieldColorGreen || fieldObjectCircle.getDiameter() > 0.2)
			m_hardObstacles.push_back(fieldObjectCircle);
		else
			m_softObstacles.push_back(i->getCircle());
    }
}

void FieldImpl::updateAchievedGoals()
{
	Point corner1(4.167, 1);
	Point corner2(4.583, 2);
	Rectangle goal(corner1, corner2);

	m_achievedGoals = 0;
	if(m_fieldObjects.size() != 0)
	{
		for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
		{
			const FieldObject &fieldObject = *i;

			if (fieldObject.getColor() == m_teamColor && goal.isInside(fieldObject.getCircle().getCenter(), 0.001))
				m_achievedGoals++;
		}
	}
	else
        m_achievedGoals = 0;
}

void FieldImpl::updateHiddenPucks()
{
    Point corner1(3.334, 0);
    Point corner2(5, 3);
    Rectangle hiddenArea(corner1, corner2);

    m_hiddenPucks = 0;
    if(m_fieldObjects.size() != 0)
    {
        for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
        {
            const FieldObject &fieldObject = *i;

            if (fieldObject.getColor() == getEnemyTeamColor() && hiddenArea.isInside(fieldObject.getCircle().getCenter(), 0.001))
                m_hiddenPucks++;
        }
    }
    else
        m_hiddenPucks = 0;
}

FieldObject &FieldImpl::getNextObjectFromPosition(Point position)
{
	vector<FieldObject>::iterator result = m_fieldObjects.begin();

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		if ( position.distanceTo((*i).getCircle().getCenter()) < position.distanceTo((*result).getCircle().getCenter()))
			result = i;
	}
	return *result;
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
	Compare positionCompare(0.15);
	Point newCenter;
	double diameter = 0.0;

	if ( positionCompare.isFuzzyEqual( fieldObject.getCircle().getCenter(), lidarObject.getCenter() ) )
	{
		newCenter  = ( fieldObject.getCircle().getCenter() + lidarObject.getCenter() ) * 0.5;
		diameter = fieldObject.getCircle().getDiameter();

		if (fieldObject.getColor() == FieldColorUnknown)
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

	m_fieldState = FieldStateCalibrated;
	removeAllFieldObjectsOutsideOfField();
}

void FieldImpl::moveCoordinateSystem(Point &newOrigin)
{
	vector<FieldObject> newSystem;

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();
		double currentDiameter = ((*i).getCircle()).getDiameter();
		Point newCenter = currentCenter - newOrigin;
		FieldColor color = (*i).getColor();

		newSystem.push_back(FieldObject(Circle(newCenter, currentDiameter), color));
	}

	Point newCenter =  m_position->getPosition() - newOrigin;
	m_position->setPosition(newCenter);

	m_odometry->setCurrentPosition(*m_position);
	assert(*m_position == m_odometry->getCurrentPosition());

	m_fieldObjects.clear();
	m_fieldObjects = newSystem;
}

void FieldImpl::rotateCoordinateSystem(double alpha)
{
	vector<FieldObject> newSystem;

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		Point currentCenter = ((*i).getCircle()).getCenter();
		double currentDiameter = ((*i).getCircle()).getDiameter();
		FieldColor color = (*i).getColor();

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

std::vector<Point> *FieldImpl::getPointsOfObjectsWithDiameterAndColor(double diameter, FieldColor color)
{
	vector<Point> *resultObjects = new vector<Point>;

	Compare compare(0.04);
	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
		if (compare.isFuzzyEqual(((*i).getCircle()).getDiameter(), diameter) && ((*i).getColor() == color || (*i).getColor() == FieldColorUnknown))
			resultObjects->push_back(((*i).getCircle()).getCenter());

	return resultObjects;
}

vector<FieldObject> FieldImpl::getObjectsWithColor(FieldColor color) const
{
	vector<FieldObject> result;

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
		if (i->getColor() == color)
			result.push_back(*i);

	return result;
}

vector<FieldObject> FieldImpl::moveAllFieldObjectsInVisibleAreaToTemporaryVector()
{
	vector<FieldObject> result;
	Point robotPosition = m_position->getPosition();
	Angle robotAngle = m_position->getOrientation();

	size_t i = 0;
	while(i < m_fieldObjects.size())
	{
		vector<FieldObject>::iterator it = m_fieldObjects.begin() + i;

		Point objectPosition = (m_fieldObjects[i].getCircle()).getCenter();
		Angle angleToXAxis(robotPosition, objectPosition);
		Angle angleToRobotDirection = angleToXAxis - robotAngle;

		if (Angle(angleToRobotDirection - m_lidar->getMaximumAngleRight()).getValueBetweenMinusPiAndPi() > 0
				&& Angle(m_lidar->getMaximumAngleLeft() - angleToRobotDirection).getValueBetweenMinusPiAndPi() > 0)
		{
			result.push_back(*it);
			m_fieldObjects.erase(it);
			--i;
		}
		++i;
	}
	return result;
}

bool FieldImpl::isPointFuzzyInsideField(const Point &point, double epsilon) const
{
	if (m_fieldState != FieldStateCalibrated)
		return true;

	return ( point.getX() < (5.0 + epsilon) && point.getX() > (0 -epsilon) && point.getY() < (3.0 + epsilon) && point.getY() > (0.0 - epsilon));
}

void FieldImpl::removeAllFieldObjectsOutsideOfField()
{	
	size_t i = 0;
	while(i < m_fieldObjects.size())
	{
		if (!isPointFuzzyInsideField(m_fieldObjects[i].getCircle().getCenter(), 0.5))
		{
			vector<FieldObject>::iterator it = m_fieldObjects.begin() + i;
			m_fieldObjects.erase(it);
			--i;
		}
		++i;
	}
}
