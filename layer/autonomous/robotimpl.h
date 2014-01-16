#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"
#include "layer/autonomous/robotstate.h"
#include "common/point.h"
#include "common/robotposition.h"

namespace RoboHockey
{
namespace Common
{
	class Watch;
	class StopWatch;
	class TimeSmoothedBoolean;
	class Logger;
}

namespace Layer
{
namespace DataAnalysis
{
	class DataAnalyser;
}

namespace Autonomous
{
	class Route;
	class Router;
	class FieldPositionChecker;

	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser, Router *router, Common::Watch *watch, Common::Logger &logger);
		virtual ~RobotImpl();

		virtual void goTo(const std::list<Common::RobotPosition> &possibleTargets);
		virtual void turnTo(const Common::Point &position);
		virtual bool stuckAtObstacle();
		virtual bool reachedTarget();
		virtual void updateActuators(const Field &field);
		virtual void updateSensorData();
		virtual void stop();
		virtual void collectPuckInFront(const Common::Point &puckPosition);
		virtual void updatePuckPosition(const Common::Point &puckPosition);
		virtual void leaveCollectedPuck();
		virtual bool isMoving() const;
		virtual void turnAround();
		virtual Common::RobotPosition getCurrentPosition() const;
		virtual Common::Point getCurrentTarget() const;
		virtual std::list<Common::Point> getAllRoutePoints() const;
		virtual bool cantReachTarget() const;
		virtual bool isPuckCollected() const;
		virtual bool isPuckCollectable() const;
		virtual bool isCollectingPuck() const;
		virtual bool isRotating() const;

		double calculateFinalSpeedForGoingStraight(const Common::Point &current, const Common::Point &next, const Common::Point &nextButOne) const;

	private:
		void clearRoute();
		bool updateRouteForTarget(const FieldPositionChecker &field, const Common::RobotPosition &target,
				const std::vector<Common::Circle> &filteredObstacles,
				bool ignoreFinalOrientation, const std::vector<Common::Circle> &hardObstacles,
				const std::vector<Common::Circle> &softObstacles);
		bool updateRoute(const Field &field);
		bool isRouteFeasible(const std::vector<Common::Circle> &obstacles) const;
		void updateEngine(const Field &field);
		void updateEngineForDrivingStraightPart(const Field &field);
		void updateEngineForDrivingTurningPart(const Field &field);
		void updateEngineForWaiting();
		void updateEngineForCollectingPuck();
		void updateEngineForLeavingPuck();
		void updateEngineForTurnAround();
		void updateEngineForTurnTo();
		void detectCollisions();
		bool enableCollisionDetectionWithSonar() const;
		void changeIntoState(RobotState state);
		bool isCurrentTargetPuckCollectable() const;
		bool checkTimeout();
		std::vector<Common::Circle> shrinkObstacles(const std::vector<Common::Circle> &obstacles) const;
		std::vector<Common::Circle> growObstacles(const std::vector<Common::Circle> &obstacles) const;
		double calculateNextFinalSpeedForGoingStraight() const;

	private:
		// forbid copies
		RobotImpl(const RobotImpl &robot);
		void operator=(const RobotImpl &robot);

	private:
		Common::Logger &m_logger;
		const double m_robotWidth;
		const double m_maximumDistanceToCollectPuck;
		const Common::Angle m_maximumAngleToCollectPuck;
		const double m_timeout;
		DataAnalysis::DataAnalyser *m_dataAnalyser;
		Router *m_router;
		Common::Watch *m_watch;
		Common::StopWatch *m_watchDog;
		bool m_tryingToTackleObstacle;
		bool m_cantReachTarget;
		Route *m_currentRoute;
		Common::RobotPosition m_currentTarget;
		std::list<Common::RobotPosition> m_possibleTargets;
		RobotState m_state;
		bool m_stateChanged;
		Common::Point m_startPosition;
		bool m_puckPositionChanged;
		bool m_rotationReached;
		bool m_ignoringSoftObstacles;
		bool m_carryingPuck;
		Common::TimeSmoothedBoolean *m_puckCollected;
		double m_finalSpeed;
	};
}
}
}

#endif
