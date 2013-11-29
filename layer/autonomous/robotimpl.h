#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"
#include "layer/autonomous/robotstate.h"
#include "common/point.h"
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
	class Route;

	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser);
		virtual ~RobotImpl();

		virtual void goTo(const Common::Point &position);
		virtual void turnTo(const Common::Point &position);
		virtual bool stuckAtObstacle();
		virtual bool reachedTarget();
		virtual void updateActuators(const Field &field);
		virtual void updateSensorData();
		virtual void stop();
		virtual void collectPuckInFront();
		virtual void leaveCollectedPuck();
		virtual bool isMoving();
		virtual void turnAround();
		virtual Common::RobotPosition getCurrentPosition();
		virtual Common::Point getCurrentTarget() const;
		virtual bool cantReachTarget() const;
		virtual bool isPuckCollected() const;
		virtual bool isPuckCollectable() const;

	private:
		void clearRoute();
		void updateRoute(const Common::Point &ownPosition, const Field &field);

	private:
		// forbid copies
		RobotImpl(const RobotImpl &robot);
		void operator=(const RobotImpl &robot);

	private:
		const double m_robotWidth;
		DataAnalysis::DataAnalyser *m_dataAnalyser;
		bool m_tryingToTackleObstacle;
		bool m_cantReachTarget;
		Route *m_currentRoute;
		Common::Point m_currentTarget;
		RobotState m_state;
	};
}
}
}

#endif
