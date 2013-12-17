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

	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser, Router *router, Common::Watch *watch);
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

	private:
		void clearRoute();
		bool updateRouteForTarget(
				const Field &field, const Common::RobotPosition &target,
				const std::vector<Common::Circle> &obstacles, bool ignoreSoftObstacles, bool ignoreFinalOrientation);
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

	private:
		// forbid copies
		RobotImpl(const RobotImpl &robot);
		void operator=(const RobotImpl &robot);

	private:
		const double m_robotWidth;
		const double m_maximumDistanceToCollectPuck;
		const Common::Angle m_maximumAngleToCollectPuck;
		DataAnalysis::DataAnalyser *m_dataAnalyser;
		Router *m_router;
		Common::Watch *m_watch;
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
	};
}
}
}

#endif
