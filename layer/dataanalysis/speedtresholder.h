#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SPEEDTRESHOLDER_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SPEEDTRESHOLDER_H

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class SpeedTresholder
	{
	public:
		SpeedTresholder();

		virtual void tresholdWheelSpeeds(double &magnitude, double &rotation) const;

	private:
		double calculateLeftWheelSpeed(double magnitude, double rotationSpeed) const;
		double calculateRightWheelSpeed(double magnitude, double rotationSpeed) const;
		double calculateMagnitude(double leftWheelSpeed, double rightWheelSpeed) const;
		double calculateRotationSpeed(double leftWheelSpeed, double rightWheelSpeed) const;
		double tresholdWheelSpeed(double wheelSpeed) const;
		double calculateRatioLeftToRightWheelSpeed(double magnitude, double rotationSpeed) const;

	private:
		const double m_wheelDiameter;
		const double m_axisLength;
		const double m_maximumWheelSpeed;
	};
}
}
}

#endif
