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
	m_engineState(EngineStateStopped)
{ }

void EngineImpl::goToStraight(const Common::Point &position)
{
	m_target = position;
	m_rotationReached = false;
	m_engineState = EngineStateDriving;
}

void EngineImpl::updateSpeedAndMagnitude()
{
	switch(m_engineState)
	{
	case EngineStateStopped: updateSpeedAndMagnitudeForStopped(); break;
	case EngineStateDriving: updateSpeedAndMagnitudeForDriving(); break;
	case EngineStateRotatingOnly: updateSpeedAndMagnitudeForRotatingOnly(); break;
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
	m_engineState = EngineStateRotatingOnly;
}

void EngineImpl::updateSpeedAndMagnitudeForStopped()
{
	m_engine.setSpeed(0, 0);
}

void EngineImpl::updateSpeedAndMagnitudeForRotatingOnly()
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
	m_engine.setSpeed(0, min(m_engine.getMaximumRotation(), orientationDifferenceToTarget + 1.1*m_engine.getMinimumSpeed()));
}

void EngineImpl::updateSpeedAndMagnitudeForDriving()
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
	double targetOrientation = atan2(positionDifference.getY(), positionDifference.getX());
	double currentOrientation = m_odometry.getCurrentOrientation();

	if (targetOrientation < 0)
		targetOrientation += 2*M_PI;
	if (currentOrientation < 0)
		currentOrientation += 2*M_PI;

	if (angleCompare.isFuzzyEqual(targetOrientation, currentOrientation))
		m_rotationReached = true;

	if (m_rotationReached)
		driveAndTurn(currentPosition, targetOrientation, currentOrientation);
	else
		turnOnly(targetOrientation, currentOrientation);
}

void EngineImpl::turnOnly(double targetOrientation, double currentOrientation)
{
	double orientationDifference = calculateOrientationDifference(targetOrientation, currentOrientation);
	double amplification = 1;
	m_engine.setSpeed(0, amplification*orientationDifference);
}

void EngineImpl::driveAndTurn(const Point &currentPosition, double targetOrientation, double currentOrientation)
{
	double distance = currentPosition.distanceTo(m_target);
	double orientationDifference = calculateOrientationDifference(targetOrientation, currentOrientation);
	double distanceAmplification = 0.5;
	double orientationAmplification = 0.5;
	m_engine.setSpeed(distanceAmplification*distance, orientationAmplification*orientationDifference);
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
