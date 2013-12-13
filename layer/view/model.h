#ifndef ROBOHOCKEY_LAYER_VIEW_MODEL_H
#define ROBOHOCKEY_LAYER_VIEW_MODEL_H

#include "layer/autonomous/fieldobject.h"
#include "common/robotposition.h"
#include "common/point.h"
#include <QtCore/QObject>
#include <vector>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Model :
			public QObject
	{
		Q_OBJECT

	public:
		Model();

		void setData(
				const std::vector<Autonomous::FieldObject> &fieldObjects,
                const std::list<Common::Point> &routeList,
				bool stuckAtObstacle, bool reachedTarget, const Common::RobotPosition &currentPosition,
				const Common::Point &currentTarget, bool isMoving, bool cantReachTarget, bool isPuckCollected,
				bool isPuckCollectable, bool closestPuckPositionValid, const Common::Point &closestPuckPosition,
				bool isRotating);
		const std::vector<Autonomous::FieldObject>& getAllFieldObjects() const;
        const std::list<Common::Point>& getAllRoutePoints();
		const std::vector<Common::Point>& getAllTargetPoints() const;
		void setTargetPoints(const std::vector<Common::Point> &targets);
		bool stuckAtObstacle() const;
		bool reachedTarget() const;
		const Common::RobotPosition& getCurrentPosition() const;
		const Common::Point getCurrentTarget() const;
		bool isMoving() const;
		void setTurnAround(bool value);
		bool getTurnAround();
		void turnToPoint(double turnToX, double turnToY);
		void setTurnTo(bool value);
		bool getTurnTo();
		void setStop(bool value);
		bool getStop();
		Common::Point getTurnPoint();
		void setCollectPuckInFront(bool value);
		bool getCollectPuckInFront();
		void setCalibratePosition(bool value);
		bool getCalibratePosition();
		void setLeavePuckInFront(bool value);
		bool getLeavePuckInFront();
		bool cantReachTarget() const;
		bool isPuckCollected() const;
		bool isPuckCollectable() const;
		bool isClosestPuckValid() const;
		const Common::Point &getClosestPuckPosition() const;
		Common::FieldColor getPuckColor() const;
		void setPuckColor(Common::FieldColor color);
		bool isRotating() const;

	signals:
		void dataForViewChanged();
		void robotDataChanged();

	private:
		std::vector<Autonomous::FieldObject> m_fieldObjects;
        std::list<Common::Point> m_routeList;
		std::vector<Common::Point> m_targetPositions;
		bool m_stuckAtObstacle;
		bool m_reachedTarget;
		Common::RobotPosition m_currentPosition;
		Common::Point m_currentTarget;
		bool m_isMoving;
		bool m_turnAround;
		bool m_stop;
		bool m_turn;
		Common::Point m_turnToPosition;
		bool m_collectPuck;
		bool m_calibratePosition;
		bool m_leavePuck;
		bool m_cantReachTarget;
		bool m_isPuckCollected;
		bool m_isPuckCollectable;
		Common::Point m_closestPuckPosition;
		bool m_closestPuckValid;
		Common::FieldColor m_puckColor;
		bool m_isRotating;
	};
}
}
}

#endif
