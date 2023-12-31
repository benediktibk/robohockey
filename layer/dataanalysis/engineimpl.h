#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H

#include "layer/dataanalysis/engine.h"
#include "common/robotposition.h"
#include "common/angle.h"

namespace RoboHockey
{
namespace Common
{
	class Watch;
	class PIDController;
	class Logger;
}

namespace Layer
{
namespace Hardware
{
	class Engine;
	class Odometry;
}

namespace DataAnalysis
{
	class SpeedTresholder;

	class EngineImpl :
			public Engine
	{
	private:
		enum EngineState { EngineStateStopped,
						   EngineStateDriving,
						   EngineStateRotating,
						   EngineStateDrivingSlowly,
						   EngineStateDrivingSlowlyBack
						 };

	public:
		EngineImpl(Hardware::Engine &engine, Hardware::Odometry &odometry, const Common::Watch &watch, Common::Logger &logger);
		virtual ~EngineImpl();

		virtual void goToStraight(const Common::Point &position);
		virtual void goToStraightSlowly(const Common::Point &position);
		virtual void goToStraightSlowlyBack(const Common::Point &position);
		virtual void updateSpeedAndRotation();
		virtual void stop();
		virtual void turnToTarget(const Common::Point &position);
		virtual void lockForwardMovement();
		virtual void unlockForwardMovement();
		virtual bool tryingToTackleObstacle();
		virtual bool reachedTarget() const;
		virtual Common::Point getCurrentTarget() const;
		virtual bool isMoving() const;
		virtual double getCurrentSpeed() const;
		virtual double getCurrentRotationSpeed() const;
		virtual void updateSensorData();

		const Common::Point& getStartPosition() const;

	private:
		void updateSpeedAndRotationForStopped();
		void updateSpeedAndRotationForDriving();
		void updateSpeedAndRotationForRotating();
		void turnOnly(const Common::Angle &targetOrientation, const Common::Angle &currentOrientation);
		void driveAndTurn(const Common::RobotPosition &currentPosition);
		void setSpeed(double magnitude, double rotationSpeed);
		void switchIntoState(EngineState state);
		void log(const std::string &message);

	private:
		Hardware::Engine &m_engine;
		Hardware::Odometry &m_odometry;
		Common::Logger &m_logger;
		Common::Point m_target;
		Common::Point m_startPosition;
		EngineState m_engineState;
		Common::Angle m_startOrientation;
		bool m_forwardMovementLocked;
		bool m_tryingToTackleObstacle;
		SpeedTresholder *m_speedTresholder;
		double m_desiredSpeed;
		bool m_isMoving;
		bool m_startedMovement;
		Common::PIDController *m_controllerTurnOnly;
		Common::PIDController *m_controllerDriveAndTurnRotation;
		Common::PIDController *m_controllerDriveAndTurnSpeed;
	};
}
}
}

#endif
