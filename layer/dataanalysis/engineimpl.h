#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H

#include "layer/dataanalysis/engine.h"
#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Engine;
	class Odometry;
}

namespace DataAnalysis
{
	class EngineImpl :
			public Engine
	{
	private:
		enum EngineState { EngineStateStopped, EngineStateRotatingOnly, EngineStateDriving };

	public:
		EngineImpl(Hardware::Engine &engine, Hardware::Odometry &odometry);

		virtual void goToStraight(const Common::Point &position);
		virtual void updateSpeedAndMagnitude();
		virtual void stop();
		virtual void turnAround();

	private:
		void updateSpeedAndMagnitudeForStopped();
		void updateSpeedAndMagnitudeForRotatingOnly();
		void updateSpeedAndMagnitudeForDriving();
		void turnOnly(double targetOrientation, double currentOrientation);
		void driveAndTurn(const Common::Point &currentPosition, double targetOrientation, double currentOrientation);
		double calculateOrientationDifference(double targetOrientation, double currentOrientation) const;
		static double fixAngleRange(double value);

	private:
		Hardware::Engine &m_engine;
		Hardware::Odometry &m_odometry;
		Common::Point m_target;
		bool m_rotationReached;
		EngineState m_engineState;
		double m_startOrientation;
		bool m_oneHalfTurnDone;
	};
}
}
}

#endif
