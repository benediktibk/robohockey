#include "layer/dataanalysis/speedtresholder.h"
#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

SpeedTresholder::SpeedTresholder() :
	m_wheelDiameter(0.19),
	m_axisLength(0.38),
	m_maximumWheelSpeed(1.7*M_PI)
{ }

void SpeedTresholder::tresholdWheelSpeeds(double &magnitude, double &rotationSpeed) const
{
	const double leftWheelSpeed = calculateLeftWheelSpeed(magnitude, rotationSpeed);
	const double rightWheelSpeed = calculateRightWheelSpeed(magnitude, rotationSpeed);
	const double leftWheelSpeedTresholded = tresholdWheelSpeed(leftWheelSpeed);
	const double rightWheelSpeedTresholded = tresholdWheelSpeed(rightWheelSpeed);
	Compare compare(0.001);

	if (compare.isFuzzyEqual(rotationSpeed, 0))
	{
		magnitude = calculateMagnitude(leftWheelSpeedTresholded, rightWheelSpeedTresholded);
		rotationSpeed = calculateRotationSpeed(leftWheelSpeedTresholded, rightWheelSpeedTresholded);
		return;
	}

	const double ratioLeftToRightWheelSpeed = calculateRatioLeftToRightWheelSpeed(magnitude, rotationSpeed);
	double finalLeftWheelSpeed = 0;
	double finalRightWheelSpeed = 0;

	if (	!compare.isFuzzyEqual(leftWheelSpeed, leftWheelSpeedTresholded) &&
			!compare.isFuzzyEqual(rightWheelSpeed, rightWheelSpeedTresholded))
	{
		if (fabs(ratioLeftToRightWheelSpeed) >= 1)
		{
			finalLeftWheelSpeed = leftWheelSpeedTresholded;
			finalRightWheelSpeed = leftWheelSpeedTresholded/ratioLeftToRightWheelSpeed;
		}
		else
		{
			finalRightWheelSpeed = rightWheelSpeedTresholded;
			finalLeftWheelSpeed = rightWheelSpeedTresholded*ratioLeftToRightWheelSpeed;
		}
	}
	else if (!compare.isFuzzyEqual(leftWheelSpeed, leftWheelSpeedTresholded))
	{
		finalLeftWheelSpeed = leftWheelSpeedTresholded;
		finalRightWheelSpeed = leftWheelSpeedTresholded/ratioLeftToRightWheelSpeed;
	}
	else if (!compare.isFuzzyEqual(rightWheelSpeed, rightWheelSpeedTresholded))
	{
		finalRightWheelSpeed = rightWheelSpeedTresholded;
		finalLeftWheelSpeed = rightWheelSpeedTresholded*ratioLeftToRightWheelSpeed;
	}
	else
	{
		finalLeftWheelSpeed = leftWheelSpeedTresholded;
		finalRightWheelSpeed = rightWheelSpeedTresholded;
	}

	finalLeftWheelSpeed = tresholdWheelSpeed(finalLeftWheelSpeed);
	finalRightWheelSpeed = tresholdWheelSpeed(finalRightWheelSpeed);
	magnitude = calculateMagnitude(finalLeftWheelSpeed, finalRightWheelSpeed);
	rotationSpeed = calculateRotationSpeed(finalLeftWheelSpeed, finalRightWheelSpeed);
}

double SpeedTresholder::calculateLeftWheelSpeed(double magnitude, double rotationSpeed) const
{
	return (2*magnitude - m_axisLength*rotationSpeed)/m_wheelDiameter;
}

double SpeedTresholder::calculateRightWheelSpeed(double magnitude, double rotationSpeed) const
{
	return (2*magnitude + m_axisLength*rotationSpeed)/m_wheelDiameter;
}

double SpeedTresholder::calculateMagnitude(double leftWheelSpeed, double rightWheelSpeed) const
{
	return m_wheelDiameter/4*(leftWheelSpeed + rightWheelSpeed);
}

double SpeedTresholder::calculateRotationSpeed(double leftWheelSpeed, double rightWheelSpeed) const
{
	return m_wheelDiameter/(2*m_axisLength)*(rightWheelSpeed - leftWheelSpeed);
}

double SpeedTresholder::tresholdWheelSpeed(double wheelSpeed) const
{
	if (wheelSpeed > m_maximumWheelSpeed)
		wheelSpeed = m_maximumWheelSpeed;
	else if (wheelSpeed < (-1)*m_maximumWheelSpeed)
		wheelSpeed = (-1)*m_maximumWheelSpeed;

	return wheelSpeed;
}

double SpeedTresholder::calculateRatioLeftToRightWheelSpeed(double magnitude, double rotationSpeed) const
{
	double ratioMagnitudeToRotationSpeed = magnitude/rotationSpeed;
	double temp = 2*ratioMagnitudeToRotationSpeed/m_axisLength;
	return (temp - 1)/(temp + 1);
}
