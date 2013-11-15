#include "layer/dataanalysis/engineimpl.h"
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
	m_tryingToTackleObstacle(false)
{ }

void EngineImpl::goToStraight(const Common::Point &position)
{
	m_target = position;
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	m_startPosition = currentRobotPosition.getPosition();
	m_rotationReached = false;
	m_engineState = EngineStateDriving;
}

void EngineImpl::updateSpeedAndRotation()
{
	switch(m_engineState)
	{
	case EngineStateStopped: updateSpeedAndRotationForStopped(); break;
	case EngineStateDriving: updateSpeedAndRotationForDriving(); break;
	case EngineStateTurnAround: updateSpeedAndRotationForTurnAround(); break;
	case EngineStateRotating: updateSpeedAndRotationForRotating(); break;
	}
}

void EngineImpl::stop()
{
	m_engineState = EngineStateStopped;
	m_tryingToTackleObstacle = false;
	m_engine.setSpeed(0, 0);
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

const Point &EngineImpl::getStartPosition() const
{
	return m_startPosition;
}

void EngineImpl::updateSpeedAndRotationForStopped()
{
	m_tryingToTackleObstacle = false;
	m_engine.setSpeed(0, 0);
}

void EngineImpl::updateSpeedAndRotationForTurnAround()
{
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	Angle currentOrientation = currentRobotPosition.getOrientation();
	Angle orientationDifference = currentOrientation - m_startOrientation;

	if (orientationDifference.getValueBetweenMinusPiAndPi() < 0)
		m_oneHalfTurnDone = true;

	if (m_oneHalfTurnDone && orientationDifference.getValueBetweenMinusPiAndPi() > 0)
	{
		stop();
		return;
	}

	double orientationDifferenceToTarget = 2*M_PI - orientationDifference.getValueBetweenZeroAndTwoPi();
	m_tryingToTackleObstacle = false;
	m_engine.setSpeed(0, min(m_engine.getMaximumRotation(), orientationDifferenceToTarget*0.75 + 1.1*m_engine.getMinimumSpeed()));
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
	Compare angleCompare(0.05);
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
	double amplification = 1;
	m_tryingToTackleObstacle = false;
	m_engine.setSpeed(0, orientationDifference.getValueBetweenMinusPiAndPi()*amplification);
}

void EngineImpl::driveAndTurn(const RobotPosition &currentPosition)
{
	Compare positionCompare(0.02);
	double totalDistance = m_startPosition.distanceTo(m_target);
	const Point &currentPositionPoint = currentPosition.getPosition();
	Angle alpha = Angle(m_target, currentPositionPoint, m_startPosition);
	Angle ownOrientation = currentPosition.getOrientation();
	Angle targetOrientation(currentPositionPoint, m_target);
	Angle orientationDifference = targetOrientation - ownOrientation;
	double distanceToTarget = currentPositionPoint.distanceTo(m_target);
	double orthogonalError = distanceToTarget*sin(orientationDifference.getValueBetweenMinusPiAndPi());
	double forwardError = max(0.0, totalDistance*cos(alpha.getValueBetweenMinusPiAndPi()));

	if (positionCompare.isFuzzyEqual(forwardError, 0))
	{
		stop();
		return;
	}

	double distanceAmplification = 0.1;
	double orientationAmplification = 1.5;
	double magnitude = distanceAmplification*forwardError;
	double rotationSpeed = orientationAmplification*orthogonalError;

	if (magnitude > 0 && m_forwardMovementLocked)
	{
		magnitude = 0;
		m_tryingToTackleObstacle = true;
	}
	else
		m_tryingToTackleObstacle = false;

	m_engine.setSpeed(magnitude, rotationSpeed);
}