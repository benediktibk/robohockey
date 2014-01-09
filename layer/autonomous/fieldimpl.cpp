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
#include "common/randomdecision.h"
#include <math.h>
#include <algorithm>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldImpl::FieldImpl(DataAnalysis::Odometry &odometry, const DataAnalysis::Lidar &lidar, DataAnalysis::Camera &camera, Robot &autonomousRobot):
	m_seenTresholdForFieldObjects(5),
	m_maximumDistanceToDeleteFieldObject(2.5),
	m_maximumAngleToDeleteFieldObject(Angle::getQuarterRotation()),
	m_odometry(&odometry),
	m_lidar(&lidar),
	m_camera(&camera),
	m_robot(&autonomousRobot),
	m_position(new Common::RobotPosition(m_odometry->getCurrentPosition())),
	m_fieldState(FieldStateUnknownPosition),
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
	updateWithOdometryData();

	if (!m_robot->isRotating())
	{
		updateWithLidarData(6.0);
		if (!m_robot->isMoving())
			updateWithCameraData();
	}
	else
		updateWithLidarData(0.3);

	tryToMergeDoubledFieldObjects();
	removeNotExistingFieldObjects();
	updateUsefulFieldObjects();

	if (!m_robot->isRotating())
		updateObstacles();

	updateAchievedGoals();
	updateHiddenPucks();
}

const vector<FieldObject> &FieldImpl::getAllFieldObjects() const
{
	return m_usefulFieldObjects;
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

unsigned int FieldImpl::getNumberOfObjectsWithColor(FieldColor color) const
{
	unsigned int result = 0;

	for (vector<FieldObject>::const_iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
		if (i->getColor() == color)
			++result;

	return result;
}

bool FieldImpl::calibratePosition()
{
	unsigned int numberOfBorderStones;
	RobotPosition newOrigin = getNewOriginFromFieldDetection(numberOfBorderStones);

	bool result = !(newOrigin.getPosition() == Point::zero()) || !(newOrigin.getOrientation().getValueBetweenMinusPiAndPi() == 0.0);

	if (result)
		transformCoordinateSystem(newOrigin);

	return result;
}

unsigned int FieldImpl::getNumberOfAchievedGoals() const
{
	return m_achievedGoals;
}

unsigned int FieldImpl::getNumberOfHiddenPucks() const
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

	double blueGoal = m_camera->getProbabilityForBlueGoal();
	double yellowGoal = m_camera->getProbabilityForYellowGoal();

	if(blueGoal > yellowGoal)
		m_teamColor = FieldColorBlue;
	else
		m_teamColor = FieldColorYellow;
}

list<RobotPosition> FieldImpl::getTargetsForGoalDetection() const
{
	list<RobotPosition> targetList;
	targetList.push_back(RobotPosition(Point(5.0/6.0 + 0.34,1.5), Angle::getHalfRotation()));

	return targetList;
}

list<RobotPosition> FieldImpl::getTargetsForScoringGoals() const
{
	list<RobotPosition> targetList;

	targetList.push_front(RobotPosition( Point(5 - 5.0/8.0 - 0.14, 1.3), Angle() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0 + 0.14, 1.3), Angle::getHalfRotation() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.3 + 0.14), Angle::getThreeQuarterRotation()));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.3 - 0.14), Angle::getQuarterRotation() ));

	targetList.push_front(RobotPosition( Point(5 - 5.0/8.0 - 0.14, 1.7), Angle() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0 + 0.14, 1.7), Angle::getHalfRotation() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.7 + 0.14), Angle::getThreeQuarterRotation()));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.7 - 0.14), Angle::getQuarterRotation() ));

	targetList.push_front(RobotPosition( Point(5 - 5.0/8.0 - 0.14, 1.5), Angle() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0 + 0.14, 1.5), Angle::getHalfRotation() ));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.5 + 0.14), Angle::getThreeQuarterRotation()));
	targetList.push_back(RobotPosition( Point(5 - 5.0/8.0, 1.5 - 0.14), Angle::getQuarterRotation() ));

	return targetList;
}

list<RobotPosition> FieldImpl::getTargetsForFinalPosition() const
{
	list<RobotPosition> targetList;

	targetList.push_back(RobotPosition( Point(3.5, 1.5), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.6), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.4), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.3), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.7), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.8), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.2), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.9), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1.1), 0));
	targetList.push_back(RobotPosition( Point(3.5, 2.0), 0));
	targetList.push_back(RobotPosition( Point(3.5, 1), 0));
	targetList.push_back(RobotPosition( Point(3.5, 0.8), 0));
	targetList.push_back(RobotPosition( Point(3.5, 2.2), 0));
	targetList.push_back(RobotPosition( Point(3.5, 2.4), 0));
	targetList.push_back(RobotPosition( Point(3.5, 0.6), 0));
	targetList.push_back(RobotPosition( Point(3.5, 2.5), 0));
	targetList.push_back(RobotPosition( Point(3.5, 0.5), 0));


	return targetList;
}

list<RobotPosition> FieldImpl::getTargetsForSearchingPucks() const
{
	vector<RobotPosition> targetVector2;
	list<RobotPosition> targetList;
	list<RobotPosition> targetList2(10);
	list<RobotPosition> targetList3;
	RandomDecision decider(0.5);
	Rectangle neutralSector(Point(5.0/3.0, 0.1), Point(10.0/3.0, 2.9));
	Rectangle neutralSector2(Point(0.1, 0.1), Point(4.9, 2.9));
	double distanceFromRobotToObject = 0.50;
	Angle angle0(0);

	for (vector<FieldObject>::const_iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
	{
		const FieldObject &fieldObject = *i;
		if(fieldObject.getColor() == FieldColorUnknown && neutralSector.isInside(fieldObject.getCircle().getCenter(), 0.01))
		{
			list<RobotPosition> listToArrange(4);
			vector<RobotPosition> targetVector;
			Angle angle1 = angle0 + Angle::convertFromDegreeToRadiant(90);
			Angle angle2 = angle0 + Angle::convertFromDegreeToRadiant(180);
			Angle angle3 = angle0 + Angle::convertFromDegreeToRadiant(270);

			Point point0(distanceFromRobotToObject, 0);
			point0.rotate(Angle::convertFromDegreeToRadiant(180) + angle0);
			point0 = point0 + fieldObject.getCircle().getCenter();

			Point point1(distanceFromRobotToObject, 0);
			point1.rotate(Angle::convertFromDegreeToRadiant(180) + angle1);
			point1 = point1 + fieldObject.getCircle().getCenter();

			Point point2(distanceFromRobotToObject, 0);
			point2.rotate(Angle::convertFromDegreeToRadiant(180) + angle2);
			point2 = point2 + fieldObject.getCircle().getCenter();

			Point point3(distanceFromRobotToObject, 0);
			point3.rotate(Angle::convertFromDegreeToRadiant(180) + angle3);
			point3 = point3 + fieldObject.getCircle().getCenter();

			targetVector.push_back(RobotPosition(point0, angle0));
			targetVector.push_back(RobotPosition(point2, angle2));

			random_shuffle(targetVector.begin(), targetVector.end());

			if(fieldObject.getCircle().getCenter().getY() > 1.5)
			{
				targetVector.push_back(RobotPosition(point1, angle1));
				targetVector.push_back(RobotPosition(point3, angle3));
			}
			else
			{
				targetVector.push_back(RobotPosition(point3, angle3));
				targetVector.push_back(RobotPosition(point1, angle1));
			}

			copy(targetVector.begin(), targetVector.end(), listToArrange.begin());

			if(decider.decide())
				targetList.splice(targetList.begin(), listToArrange);
			else
				targetList.splice((targetList.end()), listToArrange);
		}
		else if(fieldObject.getColor() == FieldColorUnknown && neutralSector2.isInside(fieldObject.getCircle().getCenter(), 0.01))
		{
			list<RobotPosition> listToArrange2(4);
			vector<RobotPosition> targetVector3;
			Angle angle1 = angle0 + Angle::convertFromDegreeToRadiant(90);
			Angle angle2 = angle0 + Angle::convertFromDegreeToRadiant(180);
			Angle angle3 = angle0 + Angle::convertFromDegreeToRadiant(270);

			Point point0(distanceFromRobotToObject, 0);
			point0.rotate(Angle::convertFromDegreeToRadiant(180) + angle0);
			point0 = point0 + fieldObject.getCircle().getCenter();

			Point point1(distanceFromRobotToObject, 0);
			point1.rotate(Angle::convertFromDegreeToRadiant(180) + angle1);
			point1 = point1 + fieldObject.getCircle().getCenter();

			Point point2(distanceFromRobotToObject, 0);
			point2.rotate(Angle::convertFromDegreeToRadiant(180) + angle2);
			point2 = point2 + fieldObject.getCircle().getCenter();

			Point point3(distanceFromRobotToObject, 0);
			point3.rotate(Angle::convertFromDegreeToRadiant(180) + angle3);
			point3 = point3 + fieldObject.getCircle().getCenter();

			targetVector3.push_back(RobotPosition(point0, angle0));
			targetVector3.push_back(RobotPosition(point2, angle2));

			random_shuffle(targetVector3.begin(), targetVector3.end());

			if(fieldObject.getCircle().getCenter().getY() > 1.5)
			{
				targetVector3.push_back(RobotPosition(point1, angle1));
				targetVector3.push_back(RobotPosition(point3, angle3));
			}
			else
			{
				targetVector3.push_back(RobotPosition(point3, angle3));
				targetVector3.push_back(RobotPosition(point1, angle1));
			}

			copy(targetVector3.begin(), targetVector3.end(), listToArrange2.begin());

			if(decider.decide())
				targetList3.splice(targetList3.begin(), listToArrange2);
			else
				targetList3.splice(targetList3.end(), listToArrange2);
		}
	}

	targetVector2.push_back(RobotPosition( Point(1.4, 2.4), Angle()));
	targetVector2.push_back(RobotPosition( Point(2.0, 1.0), Angle()));
	targetVector2.push_back(RobotPosition( Point(2.0, 2.0), Angle()));
	targetVector2.push_back(RobotPosition( Point(2.5, 2.2), Angle::getHalfRotation()));
	targetVector2.push_back(RobotPosition( Point(2.5, 2.2), Angle()));
	targetVector2.push_back(RobotPosition( Point(2.5, 0.8), Angle()));
	targetVector2.push_back(RobotPosition( Point(3.0, 1.5), Angle::getEighthRotation() + Angle::getQuarterRotation()));
	targetVector2.push_back(RobotPosition( Point(3.0, 1.5), Angle::getHalfRotation() + Angle::getQuarterRotation()));
	targetVector2.push_back(RobotPosition( Point(1.4, 0.6), Angle()));
	targetVector2.push_back(RobotPosition( Point(2.5, 0.7), Angle::getThreeQuarterRotation()));


	random_shuffle(targetVector2.begin(), targetVector2.end());

	copy(targetVector2.begin(), targetVector2.end(), targetList2.begin());

	targetList.splice(targetList.end(), targetList3);
	targetList.splice((targetList.end()), targetList2);

	return targetList;
}

list<RobotPosition> FieldImpl::getTargetsForHidingEnemyPucks() const
{
	list<RobotPosition> targets;

	targets.push_back(RobotPosition( Point(4.7, 2.33), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.7, 0.67), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.7, 2.67), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.7, 0.33), Angle::convertFromDegreeToRadiant(0)));

	targets.push_back(RobotPosition( Point(4.4, 2.33), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.4, 0.67), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.4, 2.67), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.4, 0.33), Angle::convertFromDegreeToRadiant(0)));

	targets.push_back(RobotPosition( Point(4.2, 0.67), Angle::convertFromDegreeToRadiant(50)));
	targets.push_back(RobotPosition( Point(4.2, 2.67), Angle::convertFromDegreeToRadiant(70)));
	targets.push_back(RobotPosition( Point(4.2, 0.33), Angle::convertFromDegreeToRadiant(60)));
	targets.push_back(RobotPosition( Point(4.2, 2.33), Angle::convertFromDegreeToRadiant(330)));

	targets.push_back(RobotPosition( Point(4.0, 0.50), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.0, 0.70), Angle::convertFromDegreeToRadiant(270)));
	targets.push_back(RobotPosition( Point(4.0, 2.50), Angle::convertFromDegreeToRadiant(0)));
	targets.push_back(RobotPosition( Point(4.0, 2.67), Angle::convertFromDegreeToRadiant(50)));

	targets.push_back(RobotPosition( Point(3.7, 0.33), Angle::convertFromDegreeToRadiant(70)));
	targets.push_back(RobotPosition( Point(3.7, 0.67), Angle::convertFromDegreeToRadiant(90)));
	targets.push_back(RobotPosition( Point(3.7, 2.67), Angle::convertFromDegreeToRadiant(100)));
	targets.push_back(RobotPosition( Point(3.7, 0.33), Angle::convertFromDegreeToRadiant(110)));
	targets.push_back(RobotPosition( Point(4.7, 1.50), Angle::convertFromDegreeToRadiant(90)));

	return targets;
}

list<RobotPosition> FieldImpl::getTargetsForCollectingOnePuck(FieldColor puckColor) const
{
	RandomDecision decider(0.5);
	list<RobotPosition> targetsToCollect;
	list<RobotPosition> listToArrange;
	Rectangle ownFieldSector(Point(0, 0), Point(3.7, 3));
	Rectangle sectorAboveUpperLeftHandCornerOfGoal(Point(3.7, 2), Point(4.16, 3));
	Rectangle sectorInFrontOfGoal(Point(3.7, 1), Point(4.16, 2));
	Rectangle sectorBelowLowerLeftHandCornerOfGoal(Point(3.7, 0), Point(4.16, 1));
	Rectangle sectorAboveGoal(Point(4.16, 2), Point(4.59, 3));
	Rectangle sectorBelowGoal(Point(4.16, 0), Point(4.59, 1));
	Rectangle sectorAboveUpperRightHandCornerOfGoal(Point(4.59, 2), Point(5, 3));
	Rectangle sectorBehindGoal(Point(4.59, 1), Point(5, 2));
	Rectangle sectorBelowLowerRightHandCornerOfGoal(Point(4.59,0), Point(5, 1));
	Rectangle sectorOfGoal(Point(4.16,1), Point(4.59, 2));
	Rectangle sectorOfField(Point(0, 0), Point(5,3));
	double distanceFromRobotToPuck = 0.50;

	for (vector<FieldObject>::const_iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
	{
		const FieldObject &fieldObject = *i;

		if (fieldObject.getColor() == puckColor && puckColor != FieldColorUnknown
				&& sectorOfGoal.isInside(fieldObject.getCircle().getCenter(), 0.01) == false
				&& sectorOfField.isInside(fieldObject.getCircle().getCenter(), 0.01))
		{
			Angle angle0;
			if (ownFieldSector.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif1(fieldObject.getCircle().getCenter(), Point(4.375, 1.5));
				angle0 = angleif1;
			}
			else if(sectorAboveUpperLeftHandCornerOfGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif2(fieldObject.getCircle().getCenter(), Point(4.16, 2));
				angle0 = angleif2;
			}
			else if(sectorInFrontOfGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif3(0);
				angle0 = angleif3;
			}
			else if(sectorBelowLowerLeftHandCornerOfGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif4(fieldObject.getCircle().getCenter(), Point(4.16, 1));
				angle0 = angleif4;
			}
			else if(sectorAboveGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif5(Angle::convertFromDegreeToRadiant(270));
				angle0 = angleif5;
			}
			else if(sectorBelowGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif6(Angle::convertFromDegreeToRadiant(90));
				angle0 = angleif6;
			}
			else if(sectorAboveUpperRightHandCornerOfGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif7(fieldObject.getCircle().getCenter(), Point(4.59, 2));
				angle0 = angleif7;
			}
			else if(sectorBehindGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif8(Angle::convertFromDegreeToRadiant(180));
				angle0 = angleif8;
			}
			else if(sectorBelowLowerRightHandCornerOfGoal.isInside(fieldObject.getCircle().getCenter(), 0.01))
			{
				Angle angleif9(fieldObject.getCircle().getCenter(), Point(4.59, 1));
				angle0 = angleif9;
			}

			Angle angle1 = angle0 - Angle::convertFromDegreeToRadiant(10);
			Angle angle2 = angle0 + Angle::convertFromDegreeToRadiant(10);
			Angle angle3 = angle0 - Angle::convertFromDegreeToRadiant(20);
			Angle angle4 = angle0 + Angle::convertFromDegreeToRadiant(20);
			Angle angle5 = angle0 - Angle::convertFromDegreeToRadiant(45);
			Angle angle6 = angle0 + Angle::convertFromDegreeToRadiant(45);
			Angle angle7 = angle0 - Angle::convertFromDegreeToRadiant(135);
			Angle angle8 = angle0 + Angle::convertFromDegreeToRadiant(135);
			Angle angle9 = angle0 - Angle::convertFromDegreeToRadiant(180);

			Point point0(distanceFromRobotToPuck, 0);
			point0.rotate(Angle::convertFromDegreeToRadiant(180) + angle0);
			point0 = point0 + fieldObject.getCircle().getCenter();

			Point point1(distanceFromRobotToPuck, 0);
			point1.rotate(Angle::convertFromDegreeToRadiant(180) + angle1);
			point1 = point1 + fieldObject.getCircle().getCenter();

			Point point2(distanceFromRobotToPuck, 0);
			point2.rotate(Angle::convertFromDegreeToRadiant(180) + angle2);
			point2 = point2 + fieldObject.getCircle().getCenter();

			Point point3(distanceFromRobotToPuck, 0);
			point3.rotate(Angle::convertFromDegreeToRadiant(180) + angle3);
			point3 = point3 + fieldObject.getCircle().getCenter();

			Point point4(distanceFromRobotToPuck, 0);
			point4.rotate(Angle::convertFromDegreeToRadiant(180) + angle4);
			point4 = point4 + fieldObject.getCircle().getCenter();

			Point point5(distanceFromRobotToPuck, 0);
			point5.rotate(Angle::convertFromDegreeToRadiant(180) + angle5);
			point5 = point5 + fieldObject.getCircle().getCenter();

			Point point6(distanceFromRobotToPuck, 0);
			point6.rotate(Angle::convertFromDegreeToRadiant(180) + angle6);
			point6 = point6 + fieldObject.getCircle().getCenter();

			Point point7(distanceFromRobotToPuck, 0);
			point7.rotate(Angle::convertFromDegreeToRadiant(180) + angle7);
			point7 = point7 + fieldObject.getCircle().getCenter();

			Point point8(distanceFromRobotToPuck, 0);
			point8.rotate(Angle::convertFromDegreeToRadiant(180) + angle8);
			point8 = point8 + fieldObject.getCircle().getCenter();

			Point point9(distanceFromRobotToPuck, 0);
			point9.rotate(Angle::convertFromDegreeToRadiant(180) + angle9);
			point9 = point9 + fieldObject.getCircle().getCenter();

			listToArrange.push_back(RobotPosition( point0, angle0));
			listToArrange.push_back(RobotPosition( point1, angle1));
			listToArrange.push_back(RobotPosition( point2, angle2));
			listToArrange.push_back(RobotPosition( point3, angle3));
			listToArrange.push_back(RobotPosition( point4, angle4));
			listToArrange.push_back(RobotPosition( point5, angle5));
			listToArrange.push_back(RobotPosition( point6, angle6));
			listToArrange.push_back(RobotPosition( point7, angle7));
			listToArrange.push_back(RobotPosition( point8, angle8));
			listToArrange.push_back(RobotPosition( point9, angle9));

			if(decider.decide())
				targetsToCollect.splice(targetsToCollect.begin(), listToArrange);
			else
				targetsToCollect.splice((targetsToCollect.end()), listToArrange);
		}
	}

	return targetsToCollect;
}

void FieldImpl::setTrueTeamColor(FieldColor trueTeamColor)
{
	assert(trueTeamColor != FieldColorUnknown);
	assert(trueTeamColor != FieldColorGreen);

	m_teamColor = trueTeamColor;
}

RobotPosition FieldImpl::getNewOriginFromFieldDetection(unsigned int &outNumberOfBorderstones)
{
	outNumberOfBorderstones = 0;
	vector<Point> *input = getPointsOfObjectsWithDiameterAndColor(0.06, FieldColorGreen);
	FieldDetector detector(m_position->getPosition(), *input);

	bool result = detector.tryToDetectField();

	Point newOrigin;
	double rotation = 0.0;

	if (result)
	{
		newOrigin = detector.getNewOrigin();
		rotation = detector.getRotation();
		outNumberOfBorderstones = detector.getNumberOfBorderStonesInRow();
	}

	delete input;

	return RobotPosition(newOrigin, Angle(rotation));
}

void FieldImpl::transformFieldToNewOrigin(const RobotPosition newOrigin)
{
	transformCoordinateSystem(newOrigin);
}

vector<RobotPosition> FieldImpl::getTargetsForWaitingPhase() const
{
	vector<RobotPosition> targetVector;
	targetVector.push_back(RobotPosition(Point(10.0/9.0, 2.25), Angle()));
	targetVector.push_back(RobotPosition(Point(10.0/9.0, 0.75), Angle()));
	targetVector.push_back(RobotPosition(Point(10.0/9.0, 1.50), Angle()));

	return targetVector;
}

void FieldImpl::updateWithLidarData(double range)
{
	const DataAnalysis::LidarObjects &lidarObjects =  m_lidar->getAllObjects(*m_position);
	const vector<DataAnalysis::LidarObject> &objectsInRange = lidarObjects.getObjectsWithDistanceBelow(range);

	vector<FieldObject> inVisibleArea = moveAllFieldObjectsInVisibleAreaToTemporaryVector(range);
	vector<FieldObject> partlyVisibleObjects = getAllPartlyVisibleObjects();
	updateAllNotVisibleObjects();
	vector<FieldObject> newObjects;

	for (vector<FieldObject>::iterator i = inVisibleArea.begin(); i != inVisibleArea.end(); ++i)
		i->shouldBeSeen();

	for (vector<DataAnalysis::LidarObject>::const_iterator i = objectsInRange.begin(); i != objectsInRange.end(); ++i)
	{
		const DataAnalysis::LidarObject &lidarObject = *i;

		if (!isPointFuzzyInsideField(lidarObject.getCenter(), 0.5))
			continue;

		if (inVisibleArea.size() > 0)
		{
			vector<FieldObject>::iterator currentObject = getNextObjectFromPosition(inVisibleArea, lidarObject.getCenter());
			FieldObject &nextFieldObject = *currentObject;

			if (tryToMergeLidarAndFieldObject(nextFieldObject, lidarObject))
			{
				nextFieldObject.seen();
				newObjects.push_back(nextFieldObject);
				inVisibleArea.erase(currentObject);
				continue;
			}
		}

		bool couldBeAPartlyVisibleObject = false;

		for (vector<FieldObject>::const_iterator i = partlyVisibleObjects.begin(); i != partlyVisibleObjects.end() && !couldBeAPartlyVisibleObject; ++i)
			if (couldBeTheSameObject(i->getCircle(), lidarObject))
				couldBeAPartlyVisibleObject = true;

		if (!couldBeAPartlyVisibleObject)
		{
			FieldObject object(lidarObject, FieldColorUnknown, m_seenTresholdForFieldObjects);
			object.shouldBeSeen();
			object.seen();
			newObjects.push_back(object);
		}
	}

	for (vector<FieldObject>::iterator i = inVisibleArea.begin(); i != inVisibleArea.end(); ++i)
	{
		FieldObject &fieldObject = *i;
		const Circle &circle = fieldObject.getCircle();
		const Point &ownPosition = m_position->getPosition();
		const double distance = ownPosition.distanceTo(circle.getCenter());
		const Angle angle = Angle(ownPosition, circle.getCenter()) - m_position->getOrientation();

		if (	distance < m_maximumDistanceToDeleteFieldObject &&
				fabs(angle.getValueBetweenMinusPiAndPi()) < m_maximumAngleToDeleteFieldObject.getValueBetweenZeroAndTwoPi())
			fieldObject.notSeen();
	}

	m_fieldObjects.insert(m_fieldObjects.end(), inVisibleArea.begin(), inVisibleArea.end());
	m_fieldObjects.insert(m_fieldObjects.end(), newObjects.begin(), newObjects.end());
}

void FieldImpl::tryToMergeDoubledFieldObjects()
{
	bool changed;

	do
	{
		changed = false;

		for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end() && !changed; ++i)
			for (vector<FieldObject>::iterator j = i + 1; j != m_fieldObjects.end() && !changed; ++j)
			{
				const FieldObject &firstObject = *i;
				const FieldObject &secondObject = *j;

				if (!couldBeTheSameObject(firstObject.getCircle(), secondObject.getCircle()))
					continue;

				if (firstObject.getColor() != FieldColorUnknown && secondObject.getColor() != FieldColorUnknown)
					continue;

				const Circle &firstCircle = firstObject.getCircle();
				const Circle &secondCircle = secondObject.getCircle();
				unsigned int shouldBeSeen = max(firstObject.getShouldBeSeen(), secondObject.getShouldBeSeen());
				unsigned int seen = max(firstObject.getSeen(), secondObject.getSeen());
				unsigned int notSeen = min(firstObject.getNotSeen(), secondObject.getNotSeen());
				Point center = (firstCircle.getCenter() + secondCircle.getCenter())/2;
				double diameter = (firstCircle.getDiameter() + secondCircle.getDiameter())/2;
				FieldColor color = FieldColorUnknown;

				if (firstObject.getColor() != FieldColorUnknown)
					color = firstObject.getColor();
				if (secondObject.getColor() != FieldColorUnknown)
					color = secondObject.getColor();

				FieldObject mergedObject(Circle(center, diameter), color, m_seenTresholdForFieldObjects, seen, shouldBeSeen, notSeen);
				m_fieldObjects.erase(i);
				m_fieldObjects.erase(j);
				m_fieldObjects.push_back(mergedObject);

				changed = true;
			}
	} while(changed);
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

		vector<FieldObject>::iterator nextFieldObjectIterator = getNextObjectFromPosition(currentObject.getPosition());
		FieldObject &nextFieldObject = *nextFieldObjectIterator;

		if (currentObject.getPosition().distanceTo(nextFieldObject.getCircle().getCenter()) > 0.07)
			continue;

		nextFieldObject.setColor(currentObject.getColor());
	}
}

void FieldImpl::removeNotExistingFieldObjects()
{
	vector<FieldObject> newFieldObjects;
	newFieldObjects.reserve(m_fieldObjects.size());

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		const FieldObject &object = *i;
		if (!object.isDefinitelyNotExisting())
			newFieldObjects.push_back(object);
	}

	m_fieldObjects = newFieldObjects;
}

void FieldImpl::updateUsefulFieldObjects()
{
	m_usefulFieldObjects.clear();

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		const FieldObject &object = *i;

		if (object.isMaybeExisting())
			m_usefulFieldObjects.push_back(object);
	}
}

void FieldImpl::updateObstacles()
{
	m_softObstacles.clear();
	m_hardObstacles.clear();
	m_softObstacles.reserve(m_usefulFieldObjects.size());
	m_hardObstacles.reserve(m_usefulFieldObjects.size());

	for (vector<FieldObject>::const_iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
	{
		const FieldObject &fieldObject = *i;
		Circle obstacle = fieldObject.getObstacle();

		if (fieldObject.isHardObstacle())
			m_hardObstacles.push_back(obstacle);
		else
			m_softObstacles.push_back(obstacle);
	}
}

void FieldImpl::updateAchievedGoals()
{
	Rectangle goal(Point(4.167, 1), Point(4.583, 2));

	m_achievedGoals = 0;
	for (vector<FieldObject>::const_iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
	{
		const FieldObject &fieldObject = *i;

		if (fieldObject.getColor() == m_teamColor && goal.isInside(fieldObject.getCircle().getCenter(), 0.001))
			m_achievedGoals++;
	}
}

void FieldImpl::updateHiddenPucks()
{
	Rectangle hiddenArea(Point(3.334, 0), Point(5, 3));

	m_hiddenPucks = 0;
	for (vector<FieldObject>::const_iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
	{
		const FieldObject &fieldObject = *i;

		if (fieldObject.getColor() == getEnemyTeamColor() && hiddenArea.isInside(fieldObject.getCircle().getCenter(), 0.001))
			m_hiddenPucks++;
	}
}

vector<FieldObject>::iterator FieldImpl::getNextObjectFromPosition(Point position)
{
	assert(m_fieldObjects.size() > 0);
	vector<FieldObject>::iterator result = m_fieldObjects.begin();

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
		if (position.distanceTo((*i).getCircle().getCenter()) < position.distanceTo((*result).getCircle().getCenter()))
			result = i;

	return result;
}

vector<FieldObject>::iterator FieldImpl::getNextObjectFromPosition(vector<FieldObject> &fieldObjects, Point position)
{
	assert(fieldObjects.size() > 0);
	vector<FieldObject>::iterator result = fieldObjects.begin();

	for (vector<FieldObject>::iterator i = fieldObjects.begin(); i != fieldObjects.end(); ++i)
	{
		if (position.distanceTo((*i).getCircle().getCenter()) < position.distanceTo((*result).getCircle().getCenter()))
			result = i;
	}

	return result;
}

bool FieldImpl::tryToMergeLidarAndFieldObject(FieldObject &fieldObject, const DataAnalysis::LidarObject &lidarObject)
{
	if (!couldBeTheSameObject(fieldObject.getCircle(), lidarObject))
		return false;

	Point newCenter  = (fieldObject.getCircle().getCenter() + lidarObject.getCenter())/2;
	double diameter = (fieldObject.getCircle().getDiameter() + lidarObject.getDiameter())/2;

	FieldObject mergedFieldObject(
				Circle(newCenter, diameter), fieldObject.getColor(), m_seenTresholdForFieldObjects,
				fieldObject.getSeen(), fieldObject.getShouldBeSeen(), fieldObject.getNotSeen());

	fieldObject = mergedFieldObject;
	return true;
}

bool FieldImpl::couldBeTheSameObject(const Circle &firstObject, const Circle &secondObject) const
{
	const Point &ownPosition = m_position->getPosition();
	Point objectPosition = (firstObject.getCenter() + secondObject.getCenter())/2;
	double distance = ownPosition.distanceTo(objectPosition);
	Compare positionCompare(0.1/3*distance + 0.05);
	return positionCompare.isFuzzyEqual(firstObject.getCenter(), secondObject.getCenter());
}

void FieldImpl::transformCoordinateSystem(const RobotPosition &newOrigin)
{
	moveCoordinateSystem(newOrigin.getPosition());
	rotateCoordinateSystem(newOrigin.getOrientation());

	m_fieldState = FieldStateCalibrated;
	removeAllFieldObjectsOutsideOfField();
}

void FieldImpl::moveCoordinateSystem(const Point &newOrigin)
{
	vector<FieldObject> newSystem;

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		FieldObject newObject = *i;
		Circle circle = newObject.getCircle();
		circle.setCenter(circle.getCenter() - newOrigin);
		newObject.setCircle(circle);

		newSystem.push_back(newObject);
	}

	Point newCenter =  m_position->getPosition() - newOrigin;
	m_position->setPosition(newCenter);

	m_odometry->setCurrentPosition(*m_position);
	assert(*m_position == m_odometry->getCurrentPosition());

	m_fieldObjects.clear();
	m_fieldObjects = newSystem;
}

void FieldImpl::rotateCoordinateSystem(const Angle &rotation)
{
	vector<FieldObject> newSystem;

	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		FieldObject newObject = *i;
		Circle circle = newObject.getCircle();
		Point center = circle.getCenter();
		center.rotate(rotation);
		circle.setCenter(center);
		newObject.setCircle(circle);
		newSystem.push_back(newObject);
	}

	Point ownPosition = m_position->getPosition();
	Angle ownOrientation = m_position->getOrientation();

	ownPosition.rotate(rotation);
	ownOrientation = ownOrientation + rotation;

	m_position->setPosition(ownPosition);
	m_position->setOrientation(ownOrientation);

	m_odometry->setCurrentPosition(*m_position);
	assert(*m_position == m_odometry->getCurrentPosition());

	m_fieldObjects.clear();
	m_fieldObjects = newSystem;
}

vector<Point> *FieldImpl::getPointsOfObjectsWithDiameterAndColor(double diameter, FieldColor color)
{
	vector<Point> *resultObjects = new vector<Point>;

	Compare compare(0.04);
	for (vector<FieldObject>::iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
		if (compare.isFuzzyEqual(((*i).getCircle()).getDiameter(), diameter) && ((*i).getColor() == color || (*i).getColor() == FieldColorUnknown))
			resultObjects->push_back(((*i).getCircle()).getCenter());

	return resultObjects;
}

vector<FieldObject> FieldImpl::getObjectsWithColor(FieldColor color) const
{
	vector<FieldObject> result;

	for (vector<FieldObject>::const_iterator i = m_usefulFieldObjects.begin(); i != m_usefulFieldObjects.end(); ++i)
		if (i->getColor() == color)
			result.push_back(*i);

	return result;
}

vector<FieldObject> FieldImpl::moveAllFieldObjectsInVisibleAreaToTemporaryVector(double range)
{
	vector<FieldObject> visibleObjects;
	vector<FieldObject> invisibleObjects;
	invisibleObjects.reserve(m_fieldObjects.size());
	visibleObjects.reserve(m_fieldObjects.size());
	const RobotPosition &ownPosition = m_odometry->getCurrentPosition();
	const Point &positionOnly = ownPosition.getPosition();

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		const FieldObject &fieldObject = *i;
		const Circle &circle = fieldObject.getCircle();
		bool canBeSeen = m_lidar->canBeSeen(circle, ownPosition);
		double distance = positionOnly.distanceTo(circle.getCenter());

		if (canBeSeen && distance < range)
			visibleObjects.push_back(fieldObject);
		else
			invisibleObjects.push_back(fieldObject);
	}

	m_fieldObjects = invisibleObjects;
	return visibleObjects;
}

vector<FieldObject> FieldImpl::getAllPartlyVisibleObjects() const
{
	vector<FieldObject> result;

	for (vector<FieldObject>::const_iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		const FieldObject &object = *i;
		if (m_lidar->canBeSeenPartly(object.getCircle(), *m_position))
			result.push_back(object);
	}

	return result;
}

void FieldImpl::updateAllNotVisibleObjects()
{
	for (vector<FieldObject>::iterator i = m_fieldObjects.begin(); i != m_fieldObjects.end(); ++i)
	{
		FieldObject &object = *i;

		if (!m_lidar->canBeSeenPartly(object.getCircle(), *m_position))
			object.cantBeSeen();
	}
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
