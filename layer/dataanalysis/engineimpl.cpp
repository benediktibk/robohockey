#include "layer/dataanalysis/engineimpl.h"
#include "layer/hardware/engine.h"
#include "layer/hardware/odometry.h"
#include "common/compare.h"
#include "common/point.h"
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
}

void EngineImpl::turnAround()
{
	m_startOrientation = fixAngleRange(m_odometry.getCurrentOrientation());
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

bool EngineImpl::tryingToTackleObstacle() const
{
	return m_tryingToTackleObstacle;
}

void EngineImpl::updateSpeedAndRotationForStopped()
{
	m_tryingToTackleObstacle = false;
	m_engine.setSpeed(0, 0);
}

void EngineImpl::updateSpeedAndRotationForTurnAround()
{
	double currentOrientation = fixAngleRange(m_odometry.getCurrentOrientation());
	double orientationDifference = currentOrientation - m_startOrientation;

	if (orientationDifference > M_PI)
		orientationDifference -= 2*M_PI;

	if (orientationDifference < 0)
		m_oneHalfTurnDone = true;

	if (m_oneHalfTurnDone && orientationDifference > 0)
	{
		stop();
		return;
	}

	double orientationDifferenceToTarget = 2*M_PI - fixAngleRange(orientationDifference);
	m_tryingToTackleObstacle = false;
	m_engine.setSpeed(0, min(m_engine.getMaximumRotation(), orientationDifferenceToTarget*0.75 + 1.1*m_engine.getMinimumSpeed()));
}

void EngineImpl::updateSpeedAndRotationForDriving()
{
	Point currentPosition = m_odometry.getCurrentPosition();
	Compare positionCompare(0.1);

	if (positionCompare.isFuzzyEqual(currentPosition, m_target))
	{
		stop();
		return;
	}

	Compare angleCompare(0.1);
	Point positionDifference = m_target - currentPosition;
	double targetOrientation = fixAngleRange(atan2(positionDifference.getY(), positionDifference.getX()));
	double currentOrientation = fixAngleRange(m_odometry.getCurrentOrientation());

	if (angleCompare.isFuzzyEqual(targetOrientation, currentOrientation))
		m_rotationReached = true;

	if (m_rotationReached)
		driveAndTurn(currentPosition, targetOrientation, currentOrientation);
	else
		turnOnly(targetOrientation, currentOrientation);
}

void EngineImpl::updateSpeedAndRotationForRotating()
{
	Compare angleCompare(0.1);
	Point currentPosition = m_odometry.getCurrentPosition();
	Point positionDifference = m_target - currentPosition;
	double targetOrientation = fixAngleRange(atan2(positionDifference.getY(), positionDifference.getX()));
	double currentOrientation = fixAngleRange(m_odometry.getCurrentOrientation());

	if (angleCompare.isFuzzyEqual(targetOrientation, currentOrientation))
	{
		stop();
		return;
	}

	turnOnly(targetOrientation, currentOrientation);
}

void EngineImpl::turnOnly(double targetOrientation, double currentOrientation)
{
	double orientationDifference = calculateOrientationDifference(targetOrientation, currentOrientation);
	double amplification = 1;
	m_tryingToTackleObstacle = false;
	m_engine.setSpeed(0, amplification*orientationDifference);
}

void EngineImpl::driveAndTurn(const Point &currentPosition, double targetOrientation, double currentOrientation)
{
	double distance = currentPosition.distanceTo(m_target);
	double orientationDifference = calculateOrientationDifference(targetOrientation, currentOrientation);
	double targetError = distance*sin(orientationDifference);
	double distanceAmplification = 0.5;
	double orientationAmplification = 1;
	double magnitude = distanceAmplification*distance;

	if (magnitude > 0 && m_forwardMovementLocked)
	{
		magnitude = 0;
		m_tryingToTackleObstacle = true;
	}
	else
		m_tryingToTackleObstacle = false;

	m_engine.setSpeed(magnitude, orientationAmplification*targetError);
}

double EngineImpl::calculateOrientationDifference(double targetOrientation, double currentOrientation) const
{
	double difference = targetOrientation - currentOrientation;

	if (difference > M_PI)
		difference -= 2*M_PI;
	else if (difference < (-1)*M_PI)
		difference += 2*M_PI;

	return difference;
}

double EngineImpl::fixAngleRange(double value)
{
	while (value < 0)
		value += 2*M_PI;

	unsigned int timesToHigh = value/(2*M_PI);
	value -= timesToHigh*2*M_PI;
	return value;
}
