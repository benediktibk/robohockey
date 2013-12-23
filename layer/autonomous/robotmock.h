#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTMOCK_H

#include "layer/autonomous/robot.h"
#include "common/robotposition.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class DataAnalyser;
}

namespace Autonomous
{
	class RobotMock :
			public Robot
	{
	public:
		RobotMock();

		virtual void goTo(const std::list<Common::RobotPosition> &possibleTargets);
		virtual bool stuckAtObstacle();
		virtual bool reachedTarget();
		virtual void updateActuators(const Field &field);
		virtual void updateSensorData();
		virtual void stop();
		unsigned int getCallsToUpdateActuators() const;
		unsigned int getCallsToUpdateSensorData() const;
		void setStuckAtObstacle(bool value);
		void setReachedTarget(bool value);
		const Common::RobotPosition &getLastTarget() const;
		virtual std::list<Common::Point> getAllRoutePoints() const;
		unsigned int getCallsToStop() const;
		virtual void collectPuckInFront(const Common::Point &puckPosition);
		virtual void updatePuckPosition(const Common::Point &puckPosition);
		virtual void leaveCollectedPuck();
		virtual bool isMoving() const;
		virtual void turnAround();
		virtual void turnTo(const Common::Point &position);
		virtual Common::RobotPosition getCurrentPosition() const;
		virtual Common::Point getCurrentTarget() const;
		virtual bool cantReachTarget() const;
		virtual bool isPuckCollected() const;
		virtual bool isPuckCollectable() const;
		virtual bool isCollectingPuck() const;
		virtual bool isRotating() const;

		void setIsMoving(bool value);
		void setIsRotating(bool value);
		void setCantReachedTarget(bool value);
		void setPuckCollected(bool value);
		void setPuckCollectable(bool value);
		const Common::Point &getLastTurnToTarget() const;

	private:
		Common::RobotPosition m_lastTarget;
		bool m_stuckAtObstacle;
		bool m_reachedTarget;
		unsigned int m_callsToUpdateActuators;
		unsigned int m_callsToUpdateSensorData;
		unsigned int m_callsToStop;
		bool m_isMoving;
		bool m_isRotating;
		bool m_cantReachTarget;
		bool m_puckCollected;
		bool m_puckCollectable;
		Common::Point m_lastTurnToTarget;
	};
}
}
}

#endif
