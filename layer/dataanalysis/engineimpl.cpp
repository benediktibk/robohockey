#include "layer/dataanalysis/engineimpl.h"
#include "layer/dataanalysis/speedtresholder.h"
#include "layer/hardware/engine.h"
#include "layer/hardware/odometry.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include "common/pidcontroller.h"
#include <math.h>
#include <algorithm>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

EngineImpl::EngineImpl(Hardware::Engine &engine, Hardware::Odometry &odometry, const Watch &watch) :
	m_engine(engine),
	m_odometry(odometry),
	m_engineState(EngineStateStopped),
	m_forwardMovementLocked(false),
	m_tryingToTackleObstacle(false),
	m_speedTresholder(new SpeedTresholder()),
	m_desiredSpeed(0),
	m_isMoving(false),
	m_startedMovement(false),
	m_controllerTurnOnly(new PIDController(0, 0, 0, watch)),
	m_controllerDriveAndTurnRotation(new PIDController(0, 0, 0, watch)),
	m_controllerDriveAndTurnSpeed(new PIDController(0, 0, 0, watch))
{ }

EngineImpl::~EngineImpl()
{
	delete m_speedTresholder;
	m_speedTresholder = 0;
	delete m_controllerTurnOnly;
	m_controllerTurnOnly = 0;
	delete m_controllerDriveAndTurnRotation;
	m_controllerDriveAndTurnRotation = 0;
	delete m_controllerDriveAndTurnSpeed;
	m_controllerDriveAndTurnSpeed = 0;
}

void EngineImpl::goToStraight(const Common::Point &position, double finalSpeed)
{
	switchIntoState(EngineStateDriving);
	m_target = position;
	m_finalSpeed = finalSpeed;
}

void EngineImpl::goToStraightSlowly(const Point &position)
{
	switchIntoState(EngineStateDrivingSlowly);
	m_target = position;
}

void EngineImpl::goToStraightSlowlyBack(const Point &position)
{
	switchIntoState(EngineStateDrivingSlowlyBack);
	m_target = position;
}

void EngineImpl::updateSpeedAndRotation()
{
	if (!m_startedMovement)
	{
		if (isMoving() && m_engineState != EngineStateStopped)
		{
			updateSpeedAndRotationForStopped();
			m_engine.setEnabled(true);
			return;
		}
		else
			m_startedMovement = true;
	}

	switch(m_engineState)
	{
	case EngineStateStopped:
		updateSpeedAndRotationForStopped();
		break;
	case EngineStateDriving:
	case EngineStateDrivingSlowly:
	case EngineStateDrivingSlowlyBack:
		updateSpeedAndRotationForDriving();
		break;
	case EngineStateRotating:
		updateSpeedAndRotationForRotating();
		break;
	}

	m_engine.setEnabled(!m_tryingToTackleObstacle);
}

void EngineImpl::stop()
{
	switchIntoState(EngineStateStopped);
}

void EngineImpl::turnToTarget(const Point &position)
{
	switchIntoState(EngineStateRotating);
	m_target = position;
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
	return m_isMoving;
}

double EngineImpl::getCurrentSpeed() const
{
	return (m_engine.getSpeed() + m_desiredSpeed)/2;
}

double EngineImpl::getCurrentRotationSpeed() const
{
	return m_engine.getRotationSpeed();
}

void EngineImpl::updateSensorData()
{
	m_isMoving = m_engine.isMoving();
}

bool EngineImpl::isGoingStraight() const
{
	return m_engineState == EngineStateDriving;
}

double EngineImpl::calculateSpeedForGoingStraight(double distance) const
{
	double distanceAmplification = 0.7;
	return distanceAmplification*distance;
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

void EngineImpl::updateSpeedAndRotationForDriving()
{
	RobotPosition currentPosition = m_odometry.getCurrentPosition();
	driveAndTurn(currentPosition);
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
	double amplification = 0.7;
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

	if (positionCompare.isFuzzyEqual(forwardError, 0) || alpha.isObtuse())
	{
		setSpeed(m_finalSpeed, 0);
		stop();
		return;
	}

	double orientationAmplification = 2;
	double rotationSpeed = orientationAmplification*orthogonalError;
	double magnitude = calculateSpeedForGoingStraight(forwardError) + m_finalSpeed;

	double magnitudeModification = 1 - fabs(rotationSpeed);
	if (magnitudeModification > 1)
		magnitudeModification = 1;
	else if (magnitudeModification < 0)
		magnitudeModification = 0;
	magnitude *= magnitudeModification;

	switch (m_engineState)
	{
	case EngineStateDrivingSlowly:
		magnitude = min(magnitude, 0.1);
		break;
	case EngineStateDrivingSlowlyBack:
		magnitude = -min(magnitude, 0.3);
		break;
	case EngineStateDriving:
	case EngineStateRotating:
	case EngineStateStopped:
		break;
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

void EngineImpl::switchIntoState(EngineState state)
{
	RobotPosition currentRobotPosition = m_odometry.getCurrentPosition();
	m_startPosition = currentRobotPosition.getPosition();
	m_tryingToTackleObstacle = false;
	m_finalSpeed = 0;

	if (m_engineState != state)
		m_startedMovement = false;

	m_engineState = state;
}
