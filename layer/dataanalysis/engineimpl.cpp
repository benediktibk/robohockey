#include "layer/dataanalysis/engineimpl.h"
#include "layer/dataanalysis/speedtresholder.h"
#include "layer/hardware/engine.h"
#include "layer/hardware/odometry.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include <math.h>
#include <algorithm>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

EngineImpl::EngineImpl(Hardware::Engine &engine, Hardware::Odometry &odometry) :
	m_engine(engine),
	m_odometry(odometry),
	m_rotationReached(false),
	m_engineState(EngineStateStopped),
	m_forwardMovementLocked(false),
	m_tryingToTackleObstacle(false),
	m_speedTresholder(new SpeedTresholder()),
	m_desiredSpeed(0)
{ }

EngineImpl::~EngineImpl()
{
	delete m_speedTresholder;
	m_speedTresholder = 0;
}

void EngineImpl::goToStraight(const Common::Point &position)
{
	m_target = position;
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	m_startPosition = currentRobotPosition.getPosition();
	m_rotationReached = false;
	m_engineState = EngineStateDriving;
}

void EngineImpl::goToStraightSlowly(const Point &position)
{
	m_target = position;
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	m_startPosition = currentRobotPosition.getPosition();
	m_rotationReached = false;
	m_engineState = EngineStateDrivingSlowly;
}

void EngineImpl::goToStraightThrough(const Point &position)
{
	m_target = position;
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	m_startPosition = currentRobotPosition.getPosition();
	m_rotationReached = false;
	m_engineState = EngineStateDrivingThrough;
}

void EngineImpl::updateSpeedAndRotation()
{
	switch(m_engineState)
	{
	case EngineStateStopped: updateSpeedAndRotationForStopped(); break;
	case EngineStateDriving: updateSpeedAndRotationForDriving(); break;
	case EngineStateDrivingSlowly: updateSpeedAndRotationForDriving(); break;
	case EngineStateDrivingThrough: updateSpeedAndRotationForDriving(); break;
	case EngineStateTurnAround: updateSpeedAndRotationForTurnAround(); break;
	case EngineStateRotating: updateSpeedAndRotationForRotating(); break;
	}
}

void EngineImpl::stop()
{
	m_engineState = EngineStateStopped;
	m_tryingToTackleObstacle = false;
	setSpeed(0, 0);
}

void EngineImpl::turnAround()
{
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	m_startOrientation = currentRobotPosition.getOrientation();
	m_oneHalfTurnDone = false;
	m_engineState = EngineStateTurnAround;
}

void EngineImpl::turnToTarget(const Point &position)
{
	m_target = position;
	m_engineState = EngineStateRotating;
}

void EngineImpl::lockForwardMovement()
{
	m_forwardMovementLocked = true;
}

void EngineImpl::unlockForwardMovement()
{
	m_forwardMovementLocked = false;
}

bool EngineImpl::tryingToTackleObstacle()
{
	return m_tryingToTackleObstacle;
}

bool EngineImpl::reachedTarget() const
{
	return m_engineState == EngineStateStopped;
}

Point EngineImpl::getCurrentTarget() const
{
	return m_target;
}

bool EngineImpl::isMoving() const
{
	return m_engine.isMoving();
}

double EngineImpl::getCurrentSpeed() const
{
	return (m_engine.getSpeed() + m_desiredSpeed)/2;
}

const Point &EngineImpl::getStartPosition() const
{
	return m_startPosition;
}

void EngineImpl::updateSpeedAndRotationForStopped()
{
	m_tryingToTackleObstacle = false;
	setSpeed(0, 0);
}

void EngineImpl::updateSpeedAndRotationForTurnAround()
{
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	Angle currentOrientation = currentRobotPosition.getOrientation();
	Angle orientationDifference = currentOrientation - m_startOrientation;

	if (orientationDifference.getValueBetweenMinusPiAndPi() < 0)
		m_oneHalfTurnDone = true;

	Compare angleCompare(0.1);

	if (m_oneHalfTurnDone && angleCompare.isFuzzyEqual(orientationDifference.getValueBetweenMinusPiAndPi(), 0))
	{
		stop();
		return;
	}

	double orientationDifferenceToTarget = min(M_PI/3, 2*M_PI - orientationDifference.getValueBetweenZeroAndTwoPi());
	m_tryingToTackleObstacle = false;
	setSpeed(0, orientationDifferenceToTarget);
}

void EngineImpl::updateSpeedAndRotationForDriving()
{
	RobotPosition currentPosition = m_odometry.getCurrentPosition();
	Compare angleCompare(0.1);
	Angle targetOrientation(currentPosition.getPosition(), m_target);
	Angle currentOrientation = currentPosition.getOrientation();

	if (angleCompare.isFuzzyEqual(targetOrientation, currentOrientation))
		m_rotationReached = true;

	if (m_rotationReached)
		driveAndTurn(currentPosition);
	else
		turnOnly(targetOrientation, currentOrientation);
}

void EngineImpl::updateSpeedAndRotationForRotating()
{
	Compare angleCompare(0.1);
	RobotPosition currentPosition = m_odometry.getCurrentPosition();
	Angle targetOrientation(currentPosition.getPosition(), m_target);
	Angle currentOrientation = currentPosition.getOrientation();

	if (angleCompare.isFuzzyEqual(targetOrientation, currentOrientation))
	{
		stop();
		return;
	}

	turnOnly(targetOrientation, currentOrientation);
}

void EngineImpl::turnOnly(const Angle &targetOrientation, const Angle &currentOrientation)
{
	Angle orientationDifference = targetOrientation - currentOrientation;
	double amplification = 0.5;
	m_tryingToTackleObstacle = false;
	setSpeed(0, orientationDifference.getValueBetweenMinusPiAndPi()*amplification);
}

void EngineImpl::driveAndTurn(const RobotPosition &currentPosition)
{
	Compare positionCompare(0.02);
	const Point &currentPositionPoint = currentPosition.getPosition();
	Angle alpha = Angle(m_target, currentPositionPoint, m_startPosition);
	Angle ownOrientation = currentPosition.getOrientation();
	Angle targetOrientation(currentPositionPoint, m_target);
	Angle orientationDifference = targetOrientation - ownOrientation;
	double distanceToTarget = currentPositionPoint.distanceTo(m_target);
	double orthogonalError = distanceToTarget*sin(orientationDifference.getValueBetweenMinusPiAndPi());
	double forwardError = max(0.0, distanceToTarget*cos(alpha.getValueBetweenMinusPiAndPi()));

	if (positionCompare.isFuzzyEqual(forwardError, 0))
	{
		stop();
		return;
	}

	double orientationAmplification = 1;
	double distanceAmplification = 0.5;
	double rotationSpeed = orientationAmplification*orthogonalError;
	double magnitude = distanceAmplification*forwardError;

	switch (m_engineState)
	{
	case EngineStateDrivingThrough: magnitude = 0.5; break;
	case EngineStateDrivingSlowly: magnitude = min(magnitude, 0.1); break;
	default: break;
	}

	setSpeed(magnitude, rotationSpeed);
}

void EngineImpl::setSpeed(double magnitude, double rotationSpeed)
{
	if (magnitude > 0 && m_forwardMovementLocked)
	{
		magnitude = 0;
		m_tryingToTackleObstacle = true;
	}
	else
		m_tryingToTackleObstacle = false;

	m_speedTresholder->tresholdWheelSpeeds(magnitude, rotationSpeed);
	m_desiredSpeed = magnitude;
	m_engine.setSpeed(magnitude, rotationSpeed);
}
